#!/bin/bash
set -e


sh build.sh
cd build && make install
cd .. && rm -rf build
