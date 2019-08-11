#!/bin/bash

[ ! -d "build" ] && mkdir -p "build"
cmake -B build/ -H.                                 \
    -DDEV_LIB_DIR=..                                \
    -DCMAKE_EXPORT_COMPILE_COMMANDS=ON              \
    -DCMAKE_PREFIX_PATH=$(pwd)/build/as-install/    \
    -DCMAKE_BUILD_TYPE=Release                      \
    -DAS_PRECISION_FLOAT=ON                         \
    -DAS_ROW_MAJOR=ON                               \
    -DAS_COVERAGE=ON
cmake --build build/
./build/as-test
lcov --directory build/ --capture   \
    --output-file build/app.info    \
    --gcov-tool=/usr/local/bin/gcov-7
lcov --remove build/app.info                                    \
    '*/catch2/*' '*/7.4.0/*' '*/usr/include/*'                  \
    '*/usr/local/include/*' '*/tests/catch-*' '*/tests/test-*'  \
    -o build/app-filtered.info --gcov-tool=/usr/local/bin/gcov-7
genhtml build/app-filtered.info --output-directory build/html/ --demangle-cpp
open build/html/index.html
