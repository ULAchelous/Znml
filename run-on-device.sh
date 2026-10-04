#!/usr/bin/env bash
# Push the built JNI shared library to a connected device for inspection.
# NOTE: System.loadLibrary() can only run inside an app process, so this script
# just stages libznml.so on the device; load it from your APK's Java/Kotlin code.
# Requires `adb` on PATH. Usage: ./run-on-device.sh [arm64|armv7|x86_64]
set -euo pipefail

ABI="${1:-arm64}"
case "$ABI" in
    arm64)  BUILD_DIR="build" ;;
    armv7)  BUILD_DIR="build-armv7" ;;
    x86_64) BUILD_DIR="build-x86_64" ;;
    *) echo "Unknown ABI: $ABI (use arm64|armv7|x86_64)" >&2; exit 1 ;;
esac

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
LIB="$ROOT/$BUILD_DIR/out/libznml.so"
DEVICE_DIR="/data/local/tmp/ndk-cmake-starter"

if ! command -v adb >/dev/null 2>&1; then
    echo "ERROR: adb not on PATH. Add platform-tools:" >&2
    echo "  export PATH=\"\$HOME/Library/Android/sdk/platform-tools:\$PATH\"" >&2
    exit 1
fi

if [[ ! -f "$LIB" ]]; then
    echo "ERROR: $LIB not found. Run ./build.sh $ABI first." >&2
    exit 1
fi

echo "==> Pushing $LIB to $DEVICE_DIR"
adb shell "mkdir -p $DEVICE_DIR"
adb push "$LIB" "$DEVICE_DIR/"
echo "==> Done. Load it from your app with: System.loadLibrary(\"znml\")"
