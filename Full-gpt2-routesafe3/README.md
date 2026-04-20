# Full-gpt2-routesafe3

Runtime bundle for the routed GPT-2 split3 routesafe xclbin.

## Contents

- `Full-gpt2-routesafe3.xclbin`: routed split3 routesafe bitstream.
- `host_gpt2_generate.cpp`: onboard text-generation host using `s3c0/s3c1/s3c2`.
- `gpt2_generate_io/`: tokenizer prompt, weights, cache inputs, and metadata copied from the working GPT-2 runtime bundle.
- `system.cfg`, `.ltx`, `.xclbin.info`, `.xclbin.link_summary`, and `link_routesafe_structfix_clean.log`: build/debug artifacts to keep with the xclbin.

## Build

```bash
./build_host_gpt2_generate.sh
```

If XRT is installed somewhere other than `/opt/xilinx/xrt`, set `XILINX_XRT` first.

## Run

```bash
sudo ./host_gpt2_generate ./Full-gpt2-routesafe3.xclbin ./gpt2_generate_io 30 0
```

Arguments are:

```text
host_gpt2_generate <xclbin> <gpt2_generate_io_dir> [max_new_tokens=30] [device_index=0]
```
