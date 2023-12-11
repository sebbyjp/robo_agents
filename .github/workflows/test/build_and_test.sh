#!/bin/bash
set -e

python3 -m pip install --upgrade pip
    pip3 install vcs
    sh ./setup.sh && sh  ./build.sh && sh ./test.sh
    sh ./install.sh

