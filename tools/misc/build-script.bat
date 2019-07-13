:: test for checking appveyor build_script locally (copy/move to root before running)

mkdir googletest && cd googletest
git clone --depth=10 --branch=master https://github.com/google/googletest.git .
mkdir build && cd build
cmake -G "Visual Studio 15 2017 Win64" -DCMAKE_INSTALL_PREFIX=../../tests/build/gtest_install/ -Dgtest_force_shared_crt=ON ..
cmake --build . --config Release --target install
cd ../..
mkdir build && cd build
cmake -G "Visual Studio 15 2017 Win64" -DCMAKE_INSTALL_PREFIX=../tests/build/as_install/ ..
cmake --build . --target install --config Release
cd ../tests/build
cmake -G "Visual Studio 15 2017 Win64" -DDEV_LIB_DIR=../../ .. -DCMAKE_PREFIX_PATH=%cd%\gtest_install;%cd%\as_install
cmake --build . --config Release
Release\as-test.exe