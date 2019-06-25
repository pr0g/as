# Instructions

```bash
mkdir build && cd build
# generate
cmake .. -DDEV_LIB_DIR=<path/to/library/root> # that contains CMakeLists.txt
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

# tom notes
cmake .. -DDEV_LIB_DIR=/Users/tomhultonharrop/Documents/Projects/as-math/as-math

# repeated steps
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
