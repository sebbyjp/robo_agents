#!/bin/sh

# Copyright (c) 2023 Sebastian Peralta
# 
# This software is released under the MIT License.
# https://opensource.org/licenses/MIT

# Run tests
cmake -S. -Bbuild -DBUILD_TESTS=ON ..
cmake --build build
cd build && ctest
rm -rf build
