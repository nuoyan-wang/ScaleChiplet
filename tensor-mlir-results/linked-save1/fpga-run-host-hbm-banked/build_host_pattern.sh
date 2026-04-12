#!/usr/bin/env bash
set -euo pipefail

here="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
xrt_root="${XILINX_XRT:-/opt/xilinx/xrt}"
if [[ ! -d "$xrt_root/include" ]]; then
  echo "Could not find XRT headers under $xrt_root/include."
  echo "Source /opt/xilinx/xrt/setup.sh or set XILINX_XRT."
  exit 1
fi

cxx="${CXX:-g++}"

"$cxx" -std=c++17 -O2 -Wall -Wextra \
  "$here/host_pattern.cpp" \
  -I"$xrt_root/include" \
  -L"$xrt_root/lib" \
  -Wl,-rpath,"$xrt_root/lib" \
  -lxrt_coreutil -pthread \
  -o "$here/host_base3_pattern"

echo "Built $here/host_base3_pattern"
