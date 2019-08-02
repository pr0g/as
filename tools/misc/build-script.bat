:: test for checking appveyor build_script locally (copy/move to root before running)
@echo off

if not exist catch2 mkdir catch2
cd catch2
git clone --depth=1 --branch=master https://github.com/catchorg/Catch2.git .
if not exist build mkdir build
cd build
cmake -G "Visual Studio 15 2017 Win64" -DBUILD_TESTING=OFF -DCMAKE_INSTALL_PREFIX=../../tests/build/catch2_install/ ..
cmake --build . --config Release --target install
cd ../..
if not exist build mkdir build
cd build
cmake -G "Visual Studio 15 2017 Win64" -DCMAKE_INSTALL_PREFIX=../tests/build/as_install/ ..
cmake --build . --target install --config Release
cd ../tests/build
cmake -G "Visual Studio 15 2017 Win64" -DDEV_LIB_DIR=../../ .. -DCMAKE_PREFIX_PATH=%cd%\catch2_install;%cd%\as_install
cmake --build . --config Release
Release\as-test.exe