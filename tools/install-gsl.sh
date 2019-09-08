#!/bin/bash
set -ev
mkdir gsl && cd gsl
git clone --depth=1 --branch=cmake-find-package https://github.com/pr0g/GSL.git .
mkdir build && cd build
cmake -DGSL_TEST=OFF -DCMAKE_INSTALL_PREFIX=../../tests/test/build/gsl_install/ ..
cmake --build . --target install
