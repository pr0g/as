#!/bin/bash

# options
# DAS_PRECISION_FLOAT || DAS_PRECISION_DOUBLE
# DAS_COL_MAJOR || DAS_ROW_MAJOR
# DAS_COVERAGE
# DCMAKE_BUILD_TYPE=Release || DCMAKE_BUILD_TYPE=Debug

# configure benchmarks
cmake -B build -S .                                         \
    -DCMAKE_EXPORT_COMPILE_COMMANDS=ON                      \
    -DCMAKE_PREFIX_PATH="$(pwd)/../test/third-party/build"  \
    -DCMAKE_BUILD_TYPE=Release                              \
    -DAS_PRECISION_FLOAT=ON                                 \
    -DAS_ROW_MAJOR=ON
