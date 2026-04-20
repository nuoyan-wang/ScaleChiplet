#!/usr/bin/env python3
import argparse
import json
import shutil
import struct
from pathlib import Path

import torch
from transformers import GPT2LMHeadModel, GPT2TokenizerFast


K_NUM_LAYERS = 12
K_HIDDEN = 768
K_HEADS = 12
K_HEAD_DIM = 64
K_SEQ = 128
K_CAUSAL_SEQ = 1024
K_VOCAB = 50257

ROOT = Path(__file__).resolve().parent
DEFAULT_HF_SNAPSHOT = Path(
    "/home/nu/.cache/huggingface/hub/models--gpt2/snapshots/"
    "607a30d783dfa663caf39e06633721c8d4cfcd7e"
)
STATIC_ROOT_FILES = [
    "wte.bin",
    "wpe.bin",
    "final_ln_w.bin",
    "final_ln_b.bin",
    "lm_head_w.bin",
    "token_decoder_hex.tsv",
]


def parse_args():
    ap = argparse.ArgumentParser()
    ap.add_argument("--out", required=True, help="Output gpt2_generate_io directory")
    ap.add_argument(
        "--template-dir",
        default=None,
        help="Directory containing static GPT-2 bundle tensors to reuse",
    )
    group = ap.add_mutually_exclusive_group(required=True)
    group.add_argument("--prompt", help="Prompt text")
    group.add_argument(
        "--prompt-token-ids",
        help="Comma-separated GPT-2 token ids, e.g. 464,2003,286,9552,318",
    )
    ap.add_argument("--max-new-tokens", type=int, default=30)
    ap.add_argument(
        "--model-ref",
        default=str(DEFAULT_HF_SNAPSHOT if DEFAULT_HF_SNAPSHOT.exists() else "gpt2"),
        help="Local GPT-2 snapshot path or model id",
    )
    return ap.parse_args()


def tensor_to_bf16_bytes(tensor: torch.Tensor) -> bytes:
    arr = (
        tensor.detach()
        .cpu()
        .to(torch.bfloat16)
        .contiguous()
        .view(torch.int16)
        .numpy()
        .astype("<u2", copy=False)
    )
    return arr.tobytes()


def write_bf16_tensor(path: Path, tensor: torch.Tensor):
    path.write_bytes(tensor_to_bf16_bytes(tensor))


def write_i32_file(path: Path, values):
    path.write_bytes(struct.pack("<" + "i" * len(values), *values))


def write_f32_file(path: Path, values):
    path.write_bytes(struct.pack("<" + "f" * len(values), *values))


def create_causal_mask(attention_mask: torch.Tensor, input_shape, max_seq_length: int):
    batch_size, seq_len, _ = input_shape
    expanded_mask = attention_mask[:, None, None, :].expand(batch_size, 1, seq_len, max_seq_length)
    causal_mask = torch.tril(torch.ones((seq_len, seq_len), dtype=torch.int32))
    causal_mask = causal_mask[None, None, :, :].expand(batch_size, 1, seq_len, seq_len)
    combined_mask = torch.min(expanded_mask, causal_mask)
    inverted_mask = (1.0 - combined_mask) * torch.finfo(torch.bfloat16).min
    return inverted_mask.to(dtype=torch.bfloat16)


def bundle_has_static_files(bundle_dir: Path) -> bool:
    if not bundle_dir.exists():
        return False
    if not all((bundle_dir / name).is_file() for name in STATIC_ROOT_FILES):
        return False
    if not (bundle_dir / "layer_00" / "c0_ln1_w.bin").is_file():
        return False
    return True


def copy_static_assets(template_dir: Path, out_dir: Path):
    out_dir.mkdir(parents=True, exist_ok=True)
    for name in STATIC_ROOT_FILES:
        src = template_dir / name
        if not src.is_file():
            raise FileNotFoundError(f"missing static file in template: {src}")
        shutil.copy2(src, out_dir / name)
    for layer_dir in sorted(template_dir.glob("layer_*")):
        if not layer_dir.is_dir():
            continue
        shutil.copytree(layer_dir, out_dir / layer_dir.name, dirs_exist_ok=True)


def ensure_static_assets(out_dir: Path, template_dir: Path | None):
    if bundle_has_static_files(out_dir):
        return
    if template_dir is None:
        raise RuntimeError(
            f"{out_dir} does not already contain static GPT-2 files, and no --template-dir was given"
        )
    if not bundle_has_static_files(template_dir):
        raise RuntimeError(f"template dir does not contain expected static GPT-2 files: {template_dir}")
    copy_static_assets(template_dir, out_dir)


def parse_prompt_ids(args, tokenizer):
    if args.prompt is not None:
        ids = tokenizer.encode(args.prompt, add_special_tokens=False)
        prompt_text = args.prompt
    else:
        ids = [int(x.strip()) for x in args.prompt_token_ids.split(",") if x.strip()]
        prompt_text = tokenizer.decode(ids, clean_up_tokenization_spaces=False)
    if not ids:
        raise RuntimeError("prompt token list is empty")
    return ids, prompt_text


def write_zero_cache(path: Path):
    zeros = torch.zeros((1, K_HEADS, K_SEQ, K_HEAD_DIM), dtype=torch.bfloat16)
    write_bf16_tensor(path, zeros)


def write_causal_bias(path: Path):
    bias = torch.tril(torch.ones((K_CAUSAL_SEQ, K_CAUSAL_SEQ), dtype=torch.uint8))
    bias = bias.reshape(1, 1, K_CAUSAL_SEQ, K_CAUSAL_SEQ).contiguous()
    path.write_bytes(bias.numpy().astype("uint8", copy=False).tobytes())


def write_attention_biases(out_dir: Path, prompt_length: int, max_new_tokens: int):
    attn_dir = out_dir / "attention_bias"
    if attn_dir.exists():
        shutil.rmtree(attn_dir)
    attn_dir.mkdir(parents=True, exist_ok=True)

    num_positions = min(K_SEQ, prompt_length + max_new_tokens + 1)
    for pos in range(num_positions):
        attention_mask = torch.zeros((1, K_SEQ), dtype=torch.int32)
        attention_mask[:, : pos + 1] = 1
        mask = create_causal_mask(attention_mask, torch.Size([1, 1, K_HIDDEN]), K_SEQ)
        write_bf16_tensor(attn_dir / f"pos_{pos:04d}.bin", mask)

    shutil.copy2(attn_dir / "pos_0000.bin", out_dir / "attention_bias.bin")


def generate_golden(model, tokenizer, prompt_ids, max_new_tokens: int):
    ref_ids = torch.tensor([[prompt_ids[0]]], dtype=torch.long)
    with torch.no_grad():
        ref_out = model(input_ids=ref_ids, use_cache=False, output_hidden_states=True)
    ref_logits = ref_out.logits[0, -1].detach().cpu().float()
    ref_hidden = ref_out.hidden_states[-1][0, -1].detach().cpu().reshape(1, 1, K_HIDDEN)
    top10_logits, top10_ids = torch.topk(ref_logits, 10)
    golden_next_token_id = int(top10_ids[0].item())

    input_ids = torch.tensor([prompt_ids], dtype=torch.long)
    with torch.no_grad():
        out = model(input_ids=input_ids, use_cache=True, output_hidden_states=True)
    generated_ids = list(prompt_ids)

    if max_new_tokens > 0:
        first_prompt_next = int(torch.argmax(out.logits[0, -1].detach().cpu().float()).item())
        generated_ids.append(first_prompt_next)
        past = out.past_key_values
        prev_id = first_prompt_next
        for _ in range(max_new_tokens - 1):
            step_ids = torch.tensor([[prev_id]], dtype=torch.long)
            with torch.no_grad():
                step_out = model(input_ids=step_ids, past_key_values=past, use_cache=True)
            step_logits = step_out.logits[0, -1].detach().cpu().float()
            past = step_out.past_key_values
            prev_id = int(torch.argmax(step_logits).item())
            generated_ids.append(prev_id)

    top10_records = []
    for rank, token_id in enumerate(top10_ids.tolist()):
        top10_records.append(
            {
                "rank": rank,
                "token_id": int(token_id),
                "token_text": tokenizer.decode([int(token_id)], clean_up_tokenization_spaces=False),
            }
        )

    return {
        "golden_next_token_id": golden_next_token_id,
        "golden_next_token_text": tokenizer.decode(
            [golden_next_token_id], clean_up_tokenization_spaces=False
        ),
        "golden_final_hidden": ref_hidden,
        "top10_ids": [int(x) for x in top10_ids.tolist()],
        "top10_logits": [float(x) for x in top10_logits.tolist()],
        "top10_records": top10_records,
        "generated_ids": generated_ids,
        "generated_text": tokenizer.decode(generated_ids, clean_up_tokenization_spaces=False),
    }


def write_hidden_input(path: Path, model, first_token_id: int):
    input_ids = torch.tensor([[first_token_id]], dtype=torch.long)
    position_ids = torch.tensor([[0]], dtype=torch.long)
    with torch.no_grad():
        hidden = model.transformer.wte(input_ids) + model.transformer.wpe(position_ids)
    write_bf16_tensor(path, hidden.reshape(1, 1, K_HIDDEN))


def maybe_write_decoder(tokenizer, out_dir: Path):
    decoder_path = out_dir / "token_decoder_hex.tsv"
    if decoder_path.exists():
        return
    with decoder_path.open("w", encoding="utf-8") as f:
        for token_id in range(K_VOCAB):
            text = tokenizer.decode([token_id], clean_up_tokenization_spaces=False)
            f.write(f"{token_id}\t{text.encode('utf-8').hex()}\n")


def main():
    args = parse_args()
    if args.max_new_tokens < 0:
        raise RuntimeError("--max-new-tokens must be non-negative")

    out_dir = Path(args.out).resolve()
    template_dir = Path(args.template_dir).resolve() if args.template_dir else None

    tokenizer = GPT2TokenizerFast.from_pretrained(args.model_ref, local_files_only=True)
    model = GPT2LMHeadModel.from_pretrained(
        args.model_ref, attn_implementation="eager", local_files_only=True
    )
    model = model.to(torch.bfloat16)
    model.eval()

    prompt_ids, prompt_text = parse_prompt_ids(args, tokenizer)
    if len(prompt_ids) + args.max_new_tokens > K_SEQ:
        raise RuntimeError(
            f"prompt length {len(prompt_ids)} + max_new_tokens {args.max_new_tokens} exceeds {K_SEQ}"
        )

    ensure_static_assets(out_dir, template_dir)
    maybe_write_decoder(tokenizer, out_dir)

    write_i32_file(out_dir / "prompt_token_ids.bin", prompt_ids)
    write_i32_file(out_dir / "cache_position.bin", [0])
    write_hidden_input(out_dir / "hidden_input.bin", model, prompt_ids[0])
    write_zero_cache(out_dir / "zero_key_cache.bin")
    write_zero_cache(out_dir / "zero_value_cache.bin")
    write_causal_bias(out_dir / "causal_bias.bin")
    write_attention_biases(out_dir, len(prompt_ids), args.max_new_tokens)

    golden = generate_golden(model, tokenizer, prompt_ids, args.max_new_tokens)
    write_bf16_tensor(out_dir / "golden_final_hidden.bin", golden["golden_final_hidden"])
    write_i32_file(out_dir / "golden_greedy_token_ids.bin", golden["generated_ids"])
    write_f32_file(out_dir / "golden_top10_logits.bin", golden["top10_logits"])
    write_i32_file(out_dir / "golden_top10_token_ids.bin", golden["top10_ids"])
    (out_dir / "golden_greedy_text.txt").write_text(golden["generated_text"], encoding="utf-8")
    (out_dir / "golden_top10_tokens.json").write_text(
        json.dumps(golden["top10_records"], indent=2), encoding="utf-8"
    )

    metadata = {
        "model": "gpt2",
        "prompt": prompt_text,
        "token_index": 0,
        "token_id": int(prompt_ids[0]),
        "token_text": tokenizer.decode([int(prompt_ids[0])], clean_up_tokenization_spaces=False),
        "dtype": "bf16",
        "num_layers": K_NUM_LAYERS,
        "hidden_size": K_HIDDEN,
        "num_heads": K_HEADS,
        "head_dim": K_HEAD_DIM,
        "max_seq_length": K_SEQ,
        "files_are_raw_little_endian": True,
        "bf16_files_are_uint16_storage": True,
        "golden_next_token_id": golden["golden_next_token_id"],
        "golden_next_token_text": golden["golden_next_token_text"],
        "prompt_token_ids": prompt_ids,
        "prompt_length": len(prompt_ids),
        "max_new_tokens": args.max_new_tokens,
        "has_token_decoder": (out_dir / "token_decoder_hex.tsv").exists(),
    }
    (out_dir / "metadata.json").write_text(json.dumps(metadata, indent=2), encoding="utf-8")

    print(f"Wrote GPT-2 runtime IO bundle to {out_dir}")
    print(f"prompt_length={len(prompt_ids)} max_new_tokens={args.max_new_tokens}")
    print(
        f"attention_bias_files={len(list((out_dir / 'attention_bias').glob('pos_*.bin')))} "
        f"golden_tokens={len(golden['generated_ids'])}"
    )


if __name__ == "__main__":
    main()
