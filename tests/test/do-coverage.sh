#!/bin/bash

./do-build.sh
ctest --test-dir build
lcov --directory build/ --capture                                 \
     --output-file build/app.info                                 \
     --gcov-tool=/opt/homebrew/bin/gcov-12
lcov --remove build/app.info                                      \
    '*/12.1.0/*' '*/usr/include/*'                                 \
    '*/usr/local/include/*' '*/tests/test/catch-*'                \
    '*/tests/test/*.test.*' '*/third-party/*'                     \
    -o build/app-filtered.info                                    \
    --gcov-tool=/opt/homebrew/bin/gcov-12
genhtml build/app-filtered.info --output-directory build/html/
open build/html/index.html

# note: removed --demangle-cpp from genhtml as c++filt that is called
# internally accepts '--no-strip-underscore' instead of '--no-strip-underscores',
# likely caused by version mismatch due to os/compiler update
