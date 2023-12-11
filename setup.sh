# Copyright (c) 2023 Sebastian Peralta
# 
# This software is released under the MIT License.
# https://opensource.org/licenses/MIT

#!/bin/bash
set -e

vcs import --skip-existing third_party < third_party/.repos

# TODO(speralta): Add this to Cmake using git fetch
cd third_party/gtest \
 && mkdir -p build && cd build \
 && cmake .. && sudo make install \
 && cd ../.. && rm -rf gtest