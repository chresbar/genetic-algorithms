#!/bin/bash

MESON_TEST_FLAG=""
NINJA_TEST_FLAG=""

while [[ $# -gt 0 ]]; do
    case "$1" in
        -t)
            MESON_TEST_FLAG="-Dtests=true"
            NINJA_TEST_FLAG="test"
            shift
            ;;
        *)
            echo "Unknown option: $1"
            exit 1
            ;;
    esac
done

if [ -d "builddir" ]; then
    meson setup --reconfigure builddir $MESON_TEST_FLAG
else
    meson setup builddir $MESON_TEST_FLAG
fi

echo $MESON_TEST_FLAG
ninja $NINJA_TEST_FLAG -C builddir