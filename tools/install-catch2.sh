#!/bin/bash
set -ev
mkdir catch2 && cd catch2
git clone --depth=1 --branch=devel https://github.com/catchorg/Catch2.git .
cmake -S . -B build -DBUILD_TESTING=OFF -DCMAKE_INSTALL_PREFIX=../tests/test/build/catch2_install/
cmake --build build --target install
