#!/bin/bash
set -e

mkdir -p build && cd build
cmake .. && cd ..
cmake --build build
cd ..