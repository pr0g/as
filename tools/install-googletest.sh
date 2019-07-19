#!/bin/bash
set -ev
mkdir googletest && cd googletest
git clone --depth=10 --branch=keep-inline-functions-flag https://github.com/pr0g/googletest.git .
mkdir build && cd build
cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=../../tests/build/gtest_install/ ..
cmake --build . --target install
