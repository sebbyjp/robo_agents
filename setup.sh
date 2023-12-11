# Copyright (c) 2023 Sebastian Peralta
# 
# This software is released under the MIT License.
# https://opensource.org/licenses/MIT

#!/bin/bash
set -e
# TODO(speralta): Add this to Cmake using git fetch
sudo apt-get update && sudo apt-get upgrade -y
git clone  https://github.com/google/googletest.git third_party/gtest \
 && cd third_party/gtest \
 && mkdir -p build && cd build \
 && cmake .. && sudo make install \
 && cd ../.. && rm -rf gtest