#!/bin/bash
set -ev
mkdir googletest && cd googletest
git clone --depth=10 --branch=master https://github.com/google/googletest.git .
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=../tests/test/build/gtest_install/
cmake --build build --target install
