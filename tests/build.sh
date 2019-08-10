#!/bin/bash

[ ! -d "build" ] && mkdir -p "build"
cd build/
cmake -DDEV_LIB_DIR=../.. -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -DCMAKE_PREFIX_PATH=$(pwd)/as-install/ -DCMAKE_BUILD_TYPE=Release -DAS_PRECISION_FLOAT=ON -DAS_ROW_MAJOR=ON -DAS_COVERAGE=ON ..
cmake --build .
./as-test
lcov --directory . --capture --output-file app.info --gcov-tool=/usr/local/bin/gcov-7
lcov --remove app.info '*/catch2/*' '*/7.4.0/*' '*/usr/include/*' '*/usr/local/include/*' '*/tests/catch-*' '*/tests/test-*' -o app-filtered.info --gcov-tool=/usr/local/bin/gcov-7
genhtml app-filtered.info --output-directory html/ --demangle-cpp
open html/index.html
