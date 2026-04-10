#!/usr/bin/env bash
set -euo pipefail

if [[ -z "${PLATFORM:-}" ]]; then
  echo "Set PLATFORM to your U55C .xpfm path or platform name."
  exit 1
fi

if ! command -v v++ >/dev/null 2>&1; then
  echo "v++ is not on PATH. Source /tools/Xilinx/2025.2/Vitis/settings64.sh first."
  exit 1
fi

version="$(v++ --version 2>&1 | head -n 5 || true)"
if ! grep -q "2025.2" <<<"$version"; then
  echo "Expected Vitis 2025.2, but v++ does not report 2025.2."
  echo "$version"
  exit 1
fi

here="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
vivado_jobs="${VIVADO_JOBS:-1}"
out="$here/base3_3slr_stream_2025_2_clkmeta_patch.xclbin"

common_args=(
  -t hw
  --platform "$PLATFORM"
  --link
  --save-temps
  --temp_dir "$here/_x"
  --config "$here/system.cfg"
  --vivado.synth.jobs "$vivado_jobs"
  --vivado.impl.jobs "$vivado_jobs"
  "$here/chip0_kernel/c0.xo"
  "$here/chip1_kernel/c1.xo"
  "$here/chip2_kernel/c2.xo"
  -o "$out"
)

if [[ "${SKIP_CONFIG_STEP:-0}" == "1" ]]; then
  echo "Skipping vpl.config_hw_runs because SKIP_CONFIG_STEP=1."
else
  echo "Running link through vpl.config_hw_runs..."
  v++ "${common_args[@]}" --to_step vpl.config_hw_runs
fi

vpl_dir="$here/_x/link/vivado/vpl"
good="$vpl_dir/.local/hw_platform/iprepo/ipdefs/other_ipdefs/clk_metadata_adapter_v1_0/hdl/clk_metadata_adapter_v1_0_vl_rfs.v"
fallback_good="$here/../vitis_base3_3slr_stream_2025_1/_x/link/vivado/vpl/.local/hw_platform/iprepo/ipdefs/other_ipdefs/clk_metadata_adapter_v1_0/hdl/clk_metadata_adapter_v1_0_vl_rfs.v"

if [[ ! -f "$good" ]]; then
  if [[ -f "$fallback_good" ]]; then
    echo "Using fallback working other_ipdefs clk_metadata_adapter HDL:"
    good="$fallback_good"
  else
    echo "Could not find working other_ipdefs clk_metadata_adapter HDL:"
    echo "$good"
    echo "$fallback_good"
    echo "If $vpl_dir does not exist, clean _x and rerun this script with Vitis 2025.2."
    exit 1
  fi
fi

mapfile -t targets < <(
  find "$vpl_dir" -type f \( \
    -path "*/pxi_ii_infra/clk_metadata_adapter_v1_0/hdl/clk_metadata_adapter_v1_0_vl_rfs.v" -o \
    -path "*/prj.gen/*/ipshared/*/hdl/clk_metadata_adapter_v1_0_vl_rfs.v" \
  \) | sort
)

if [[ "${#targets[@]}" -eq 0 ]]; then
  echo "No broken clk_metadata_adapter HDL targets found to patch."
  echo "Expected generated files under: $vpl_dir"
  echo "If $vpl_dir does not exist, clean _x and rerun this script with Vitis 2025.2."
  exit 1
fi

echo "Using working HDL:"
sha256sum "$good"
echo "Patching ${#targets[@]} generated clk_metadata_adapter HDL file(s)..."
for target in "${targets[@]}"; do
  echo "  $target"
  chmod u+w "$target"
  cp "$good" "$target"
done

echo "Patched target checksums:"
sha256sum "${targets[@]}"

echo "Resuming link from vpl.synth..."
if ! v++ "${common_args[@]}" --from_step vpl.synth; then
  echo "Resume from vpl.synth failed; retrying with VPL-local step name synth..."
  v++ "${common_args[@]}" --from_step synth
fi
