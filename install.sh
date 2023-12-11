#!/bin/sh

# Copyright (c) 2023 Sebastian Peralta
# 
# This software is released under the MIT License.
# https://opensource.org/licenses/MIT


sh build.sh
cd build && make install
cd .. && rm -rf build
