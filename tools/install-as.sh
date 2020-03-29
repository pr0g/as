#!/bin/bash
set -ev
cmake -S . -B build -DCMAKE_INSTALL_PREFIX=./tests/test/build/as_install/
cmake --build build --target install
