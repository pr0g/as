#!/bin/bash
set -ev
mkdir gsl && cd gsl
git clone --depth=1 https://github.com/microsoft/GSL.git .
cmake -S . -B build -DGSL_TEST=OFF -DGSL_INSTALL=ON -DCMAKE_INSTALL_PREFIX=../tests/test/build/gsl_install/
cmake --build build --target install
