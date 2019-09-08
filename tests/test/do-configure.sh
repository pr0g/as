#!/bin/bash

# options
# DAS_PRECISION_FLOAT || DAS_PRECISION_DOUBLE
# DAS_COL_MAJOR || DAS_ROW_MAJOR
# DAS_COVERAGE
# DCMAKE_BUILD_TYPE=Release || DCMAKE_BUILD_TYPE=Debug

# build
# DCMAKE_EXPORT_COMPILE_COMMANDS
# DCMAKE_PREFIX_PATH

[ ! -d "as-build" ] && mkdir -p "as-build"
[ ! -d "build" ] && mkdir -p "build"

# configure and install as
cmake -B as-build/ -S ../.. -DCMAKE_INSTALL_PREFIX=build/as-install
cmake --build as-build/ --target install

# configure tests
cmake -B build/ -S .                                \
    -DDEV_LIB_DIR=../..                             \
    -DCMAKE_EXPORT_COMPILE_COMMANDS=ON              \
    -DCMAKE_PREFIX_PATH=$(pwd)/build/as-install/    \
    -DCMAKE_BUILD_TYPE=Debug                        \
    -DAS_PRECISION_FLOAT=ON                         \
    -DAS_ROW_MAJOR=ON                               \
    -DAS_COVERAGE=ON
