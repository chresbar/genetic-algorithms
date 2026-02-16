#!/bin/bash

MESON_TEST_FLAG=""
NINJA_TEST_FLAG=""
MESON_BUILD_TYPE=""

while [[ $# -gt 0 ]]; do
    case "$1" in
        -t)
            MESON_TEST_FLAG="-Dtests=true"
            NINJA_TEST_FLAG="test"
            shift
            ;;
        -d)
            MESON_BUILD_TYPE="--buildtype=debug"
            shift
            ;;
        *)
            echo "Unknown option: $1"
            exit 1
            ;;
    esac
done

if [ -d "builddir" ]; then
    meson setup --reconfigure builddir $MESON_TEST_FLAG $MESON_BUILD_TYPE
else
    meson setup builddir $MESON_TEST_FLAG $MESON_BUILD_TYPE
fi

echo "Build type: ${MESON_BUILD_TYPE:-default}"
echo "Tests enabled: ${MESON_TEST_FLAG:-false}"

ninja $NINJA_TEST_FLAG -C builddir