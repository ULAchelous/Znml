#!/usr/bin/env bash
# Configure + build via CMake presets (see CMakePresets.json).
# Usage: ./build.sh [arm64|armv7|x86_64]
set -euo pipefail

ABI="${1:-arm64}"
case "$ABI" in
    arm64)  PRESET="android-arm64" ;;
    armv7)  PRESET="android-armv7" ;;
    x86_64) PRESET="android-x86_64" ;;
    *) echo "Unknown ABI: $ABI (use arm64|armv7|x86_64)" >&2; exit 1 ;;
esac

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
cd "$ROOT"

echo "==> Preset: $PRESET"
cmake --preset "$PRESET"
cmake --build --preset "$PRESET"

echo
echo "==> Done. To push and run on a device: ./run-on-device.sh $ABI"
