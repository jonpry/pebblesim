#!/bin/sh
gcc sample.c pebble.c sin.c image.c -o pbl -lm
# arm-linux-gnueabi-gcc-4.6 rotations.c pebble.c sin.c image.c -o pbl.arm -lm -static -mthumb
