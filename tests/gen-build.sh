#!/bin/bash

# options
# DAS_PRECISION_FLOAT || DAS_PRECISION_DOUBLE
# DAS_COL_MAJOR || DAS_ROW_MAJOR
# DAS_COVERAGE
# DCMAKE_BUILD_TYPE=Release || DCMAKE_BUILD_TYPE=Debug

# build
# DCMAKE_EXPORT_COMPILE_COMMANDS
# DCMAKE_PREFIX_PATH

[ ! -d "build" ] && mkdir -p "build"
cmake -B build/ -H. -DDEV_LIB_DIR=..                \
    -DCMAKE_EXPORT_COMPILE_COMMANDS=ON              \
    -DCMAKE_PREFIX_PATH=$(pwd)/build/as-install/    \
    -DCMAKE_BUILD_TYPE=Release                      \
    -DAS_PRECISION_FLOAT=ON                         \
    -DAS_COL_MAJOR=ON                               \
    -DAS_COVERAGE=ON
cmake --build build/
