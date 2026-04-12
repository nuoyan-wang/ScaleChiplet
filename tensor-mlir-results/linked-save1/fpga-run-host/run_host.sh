#!/usr/bin/env bash
set -euo pipefail

here="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
xclbin="${1:-$here/base3_3slr_stream_2025_2_clkmeta_patch.xclbin}"
iterations="${2:-1}"

if [[ -f /opt/xilinx/xrt/setup.sh ]]; then
  # shellcheck disable=SC1091
  source /opt/xilinx/xrt/setup.sh
fi

exec "$here/host_base3" "$xclbin" "$iterations"
