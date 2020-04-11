cmake_minimum_required(VERSION 3.15)

project(as-bench VERSION 0.0.1 LANGUAGES CXX)

find_package(as REQUIRED)
find_package(Catch2 REQUIRED)

add_executable(
    ${PROJECT_NAME}
    main.cpp as-vec.bench.cpp)

set_target_properties(
    ${PROJECT_NAME} PROPERTIES
    CXX_STANDARD 11
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO)
target_compile_features(
    ${PROJECT_NAME} PRIVATE cxx_std_11)
target_compile_definitions(
    ${PROJECT_NAME} PRIVATE
    CATCH_CONFIG_ENABLE_BENCHMARKING
    $<$<BOOL:${AS_PRECISION_FLOAT}>:AS_PRECISION_FLOAT>
    $<$<BOOL:${AS_PRECISION_DOUBLE}>:AS_PRECISION_DOUBLE>
    $<$<BOOL:${AS_COL_MAJOR}>:AS_COL_MAJOR>
    $<$<BOOL:${AS_ROW_MAJOR}>:AS_ROW_MAJOR>)
target_link_libraries(
    ${PROJECT_NAME}
    as::as Catch2::Catch2)
