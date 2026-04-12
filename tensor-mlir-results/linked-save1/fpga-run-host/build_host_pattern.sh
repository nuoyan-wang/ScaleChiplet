#!/usr/bin/env bash
set -euo pipefail

here="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
xrt_root="${XILINX_XRT:-/opt/xilinx/xrt}"
vitis_root="${XILINX_VITIS:-/tools/Xilinx/2025.2/Vitis}"
vitis_install="$(cd "$vitis_root/.." && pwd)"
fpo_lib="$vitis_install/lnx64/tools/fpo_v7_1"
cxx="${CXX:-g++}"

"$cxx" -std=c++17 -O2 -Wall -Wextra \
  "$here/host_pattern.cpp" \
  -I"$xrt_root/include" \
  -I"$vitis_root/include" \
  -L"$xrt_root/lib" \
  -L"$fpo_lib" \
  -Wl,--disable-new-dtags \
  -Wl,-rpath,"$xrt_root/lib" \
  -Wl,-rpath,"$fpo_lib" \
  -lxrt_coreutil -lIp_floating_point_v7_1_bitacc_cmodel -lgmp -lmpfr -pthread \
  -o "$here/host_base3_pattern"

echo "Built $here/host_base3_pattern"
