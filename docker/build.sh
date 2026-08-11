#!/bin/bash
#   docker build -t sumotori-build docker
#   docker run --rm -v "$PWD:/src" sumotori-build docker/build.sh
set -euo pipefail

source_dir="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
build_root="${source_dir}/build-docker"
dist="${source_dir}/dist"
targets="${*:-linux windows}"

mkdir -p "${dist}"
produced=()

configure_common=(
  -G Ninja
  -DCMAKE_BUILD_TYPE=Release
  -DSUMO_BUILD_PORTABLE=ON
  -DSUMO_SDL_VERSION=3
  -DPython_EXECUTABLE=/usr/bin/python3
)

for target in ${targets}; do
  case "${target}" in
    linux)
      build="${build_root}/linux-x64"
      cmake -S "${source_dir}" -B "${build}" "${configure_common[@]}"
      cmake --build "${build}"
      strip --strip-all "${build}/sumotori"
      cp "${build}/sumotori" "${dist}/sumotori-linux-x64"
      produced+=("${dist}/sumotori-linux-x64")
      ;;
    windows)
      build="${build_root}/windows-x64"
      cmake -S "${source_dir}" -B "${build}" "${configure_common[@]}" \
        -DCMAKE_TOOLCHAIN_FILE="${source_dir}/docker/toolchain-mingw64.cmake"
      cmake --build "${build}"
      x86_64-w64-mingw32-strip --strip-all "${build}/sumotori.exe"
      cp "${build}/sumotori.exe" "${dist}/sumotori-windows-x64.exe"
      produced+=("${dist}/sumotori-windows-x64.exe")
      ;;
    *)
      echo "unknown target: ${target}" >&2
      exit 1
      ;;
  esac
done

echo
echo "artifacts:"
for artifact in "${produced[@]}"; do
  printf '  %-34s %9s bytes  %s\n' \
    "$(basename "${artifact}")" \
    "$(stat -c %s "${artifact}")" \
    "$(file -b "${artifact}" | cut -c1-58)"
done
