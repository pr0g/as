# Instructions

```bash
mkdir build && cd build
# generate
cmake .. -DDEV_LIB_DIR=<path/to/library/root> # that contains CMakeLists.txt
# actual - cmake .. -DDEV_LIB_DIR=../../
# build
cmake --build .
#run
./as-test
mkdir coverage && cd coverage
# coverage
gcov ../../*.cpp -o ../CMakeFiles/as-test.dir/ # *.cpp are test files that ran
# *.gcov files will be generated in coverage/ folder
# gcov ../CMakeFiles/as-test.dir/*.cpp.gcno
# report
lcov --capture --directory ../../ --output-file coverage.info
# view
genhtml coverage.info --output-directory out
cd out
open index.html # to view report
```

```bash
# gcov method
cmake --build . --target scrub
cmake ..
cmake --build .
./as-test
cd coverage
gcov ../../test-vec.cpp -o ../CMakeFiles/as-test.dir/test-vec.cpp.gcno
lcov --capture --directory ../../ --output-file coverage.info
genhtml coverage.info --output-directory out
open out/index.html
```

```bash
# gcov alternate method
mkdir coverage && cd coverage
xcrun llvm-cov gcov -f -b ../CMakeFiles/as-test.dir/*.gcda
lcov --capture --directory ../../ --output-file coverage.info
genhtml coverage.info --output-directory out
open out/index.html
```

```bash
# llvm-cov method
cmake ..
cmake --build .
./as-test
xcrun llvm-profdata merge -o as-test.profdata default.profraw
xcrun llvm-cov show ./as-test -instr-profile=as-test.profdata > as-test-out.txt
```

```bash
# lcov method (http://ltp.sourceforge.net/coverage/lcov/readme.php)
# cd build/ folder
lcov --directory . --zerocounters
./as-test
lcov --directory . --capture --output-file app.info
lcov --remove app.info '/usr/local/include/gmock/*' '/usr/local/include/gtest/*' '*/v1/*' -o app-filtered.info
genhtml app-filtered.info
```
