#!/bin/bash
set -ev
mkdir build && cd build
cmake .. -DCMAKE_INSTALL_PREFIX=../tests/build/as_install/ ..
cmake --build . --target install
