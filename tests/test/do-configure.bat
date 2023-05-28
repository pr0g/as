@echo off

cmake -B build                                      ^
    -DCMAKE_PREFIX_PATH="%cd%/third-party/build"    ^
    -DCMAKE_BUILD_TYPE=Debug                        ^
    -DAS_PRECISION_FLOAT=ON                         ^
    -DAS_ROW_MAJOR=ON                               