#!/bin/bash

[ ! -d "build" ] && mkdir -p "build"
cd build/
cmake -DDEV_LIB_DIR=../.. ..
cmake --build .
./as-test
lcov --directory . --capture --output-file app.info --gcov-tool=/usr/local/bin/gcov-7
lcov --remove app.info '*/catch2/*' '*/7.4.0/*' '*/usr/include/*' '*/tests/*' -o app-filtered.info --gcov-tool=/usr/local/bin/gcov-7
genhtml app-filtered.info --output-directory html/ --demangle-cpp
open html/index.html
