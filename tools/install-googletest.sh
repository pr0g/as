#!/bin/bash
set -ev
mkdir googletest && cd googletest
git clone --depth=10 --branch=master https://github.com/google/googletest.git .
mkdir build && cd build
cmake -DCMAKE_INSTALL_PREFIX=../../tests/build/gtest_install/ ..
cmake --build . --target install