cmake_minimum_required(VERSION 3.15)

project(
    as-bench
    VERSION 0.0.1
    LANGUAGES CXX)

if(NOT DEFINED DEV_LIB_DIR)
    message(
        FATAL_ERROR
            " Please provide the path to the library in active development.\n"
            " Example: cmake -DDEV_LIB_DIR=<path/to/library/in/development>")
endif()

include(FetchContent)

FetchContent_Declare(
    cmake-helpers
    GIT_REPOSITORY https://github.com/pr0g/cmake-helpers.git
    GIT_TAG origin/main)
FetchContent_MakeAvailable(cmake-helpers)
list(APPEND CMAKE_MODULE_PATH ${cmake-helpers_SOURCE_DIR})

include(auto-install)
install_it(${DEV_LIB_DIR})

find_package(as REQUIRED)
find_package(Catch2 REQUIRED)

add_executable(${PROJECT_NAME} main.cpp as-vec.bench.cpp as-affine.bench.cpp
                               as-mat.bench.cpp)

set_target_properties(
    ${PROJECT_NAME} PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED YES
                               CXX_EXTENSIONS NO)
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)
target_compile_definitions(
    ${PROJECT_NAME}
    PRIVATE CATCH_CONFIG_ENABLE_BENCHMARKING
            $<$<BOOL:${AS_PRECISION_FLOAT}>:AS_PRECISION_FLOAT>
            $<$<BOOL:${AS_PRECISION_DOUBLE}>:AS_PRECISION_DOUBLE>
            $<$<BOOL:${AS_COL_MAJOR}>:AS_COL_MAJOR>
            $<$<BOOL:${AS_ROW_MAJOR}>:AS_ROW_MAJOR>)
target_link_libraries(${PROJECT_NAME} as::as Catch2::Catch2)
