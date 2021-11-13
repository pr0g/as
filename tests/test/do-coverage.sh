#!/bin/bash

./do-build.sh
./build/as-test
lcov --directory build/ --capture                                 \
     --output-file build/app.info                                 \
     --gcov-tool=/usr/local/bin/gcov-10
lcov --remove build/app.info                                      \
    '*/10.3.0/*' '*/usr/include/*'                                 \
    '*/usr/local/include/*' '*/tests/test/catch-*'                \
    '*/tests/test/*.test.*' '*/third-party/*'                     \
    -o build/app-filtered.info                                    \
    --gcov-tool=/usr/local/bin/gcov-10
genhtml build/app-filtered.info --output-directory build/html/
open build/html/index.html

# note: removed --demangle-cpp from genhtml as c++filt that is called
# internally accepts '--no-strip-underscore' instead of '--no-strip-underscores',
# likely caused by version mismatch due to os/compiler update
