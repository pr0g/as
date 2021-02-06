cmake_minimum_required(VERSION 3.15)

project(
    as-bench
    VERSION 0.0.1
    LANGUAGES CXX)

include(FetchContent)

FetchContent_Declare(
    as
    SOURCE_DIR ../../../)
FetchContent_MakeAvailable(as)

find_package(Catch2 CONFIG REQUIRED)

add_executable(${PROJECT_NAME} as-vec.bench.cpp as-affine.bench.cpp
                               as-mat.bench.cpp as-rigid.bench.cpp)

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
target_link_libraries(${PROJECT_NAME} as Catch2::Catch2WithMain)
