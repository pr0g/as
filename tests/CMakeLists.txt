cmake_minimum_required(VERSION 3.8)

project(as-test VERSION 0.0.1 LANGUAGES CXX)

find_package(as REQUIRED)
find_package(GTest REQUIRED)

add_executable(
    ${PROJECT_NAME}
    main.cpp test-affine.cpp
    test-mat.cpp test-point.cpp
    test-quat.cpp test-vec.cpp)

target_compile_features(
    ${PROJECT_NAME} PRIVATE cxx_std_17)
target_compile_definitions(
    ${PROJECT_NAME} PRIVATE AS_PRECISION_FLOAT AS_COL_MAJOR)
target_link_libraries(
    ${PROJECT_NAME} as::as GTest::GTest GTest::Main)
