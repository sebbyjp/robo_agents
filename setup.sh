# Copyright (c) 2023 Sebastian Peralta
# 
# This software is released under the MIT License.
# https://opensource.org/licenses/MIT

#!/bin/bash
git clone https://github.com/google/googletest.git && cd googletest \
 && mkdir -p build && cd build \
 && cmake .. && sudo make install \
 && cd ../.. && rm -rf googletest