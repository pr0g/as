#!/bin/bash
set -ev
mkdir catch2 && cd catch2
git clone --depth=10 --branch=master https://github.com/catchorg/Catch2.git .
mkdir build && cd build
cmake -DBUILD_TESTING=OFF -DCATCH_CONFIG_DISABLE_EXCEPTIONS=1 -DCMAKE_INSTALL_PREFIX=../../tests/build/catch2_install/ ..
cmake --build . --target install