cmake_minimum_required(VERSION 3.15)

project(as-test VERSION 0.0.1 LANGUAGES CXX)

if (NOT DEFINED DEV_LIB_DIR)
    message(FATAL_ERROR
        " Please provide the path to the library in active development.\n"
        " Example: cmake -DDEV_LIB_DIR=<path/to/library/in/development>")
endif()

include(autoinstall.cmake)
install_it(${DEV_LIB_DIR})

find_package(as REQUIRED)
find_package(Catch2 REQUIRED)
find_package(Microsoft.GSL CONFIG REQUIRED)

enable_testing()

add_executable(
    ${PROJECT_NAME}
    main.cpp as-affine.test.cpp
    as-mat.test.cpp as-point.test.cpp
    as-quat.test.cpp as-vec.test.cpp
    as-math.test.cpp as-view.test.cpp)

add_test(NAME as.test.all COMMAND ${PROJECT_NAME})

string(
    APPEND coverage_options
    "$<"
        "$<AND:"
            "$<COMPILE_LANGUAGE:CXX>,"
            "$<CXX_COMPILER_ID:GNU>,"
            "$<BOOL:${AS_COVERAGE}>"
        ">:"
        "{options}"
    ">"
)

string(
    REPLACE "{options}" "-coverage;-g;-O0;-fno-inline;" # gcov
    compile_options "${coverage_options}"
)

string(
    REPLACE "{options}" "-coverage;" # gcc
    link_options "${coverage_options}"
)

string(
    APPEND compile_options
    "$<"
        "$<AND:"
            "$<COMPILE_LANGUAGE:CXX>,"
            "$<OR:"
                "$<CXX_COMPILER_ID:Clang>,"
                "$<CXX_COMPILER_ID:AppleClang>"
            ">"
        ">:"
        "-Weverything;-Wno-c++98-compat;-Wno-;-Wno-global-constructors;-Wno-"
    ">"
    "$<"
        "$<AND:"
            "$<COMPILE_LANGUAGE:CXX>,"
            "$<CXX_COMPILER_ID:MSVC>"
        ">:"
        "/W4;/WX;"
    ">"
    "$<"
        "$<AND:"
            "$<COMPILE_LANGUAGE:CXX>,"
            "$<CXX_COMPILER_ID:GNU>"
        ">:"
        "-Wall;-Wextra;-Wshadow;"
    ">"
)

target_compile_options(
    ${CMAKE_PROJECT_NAME} PRIVATE "${compile_options}")
target_link_options(
    ${CMAKE_PROJECT_NAME} PRIVATE "${link_options}")
set_target_properties(
    ${PROJECT_NAME} PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
    NO_SYSTEM_FROM_IMPORTED true)
target_compile_features(
    ${PROJECT_NAME} PRIVATE cxx_std_14)
target_compile_definitions(
    ${PROJECT_NAME} PRIVATE
    $<$<BOOL:${AS_PRECISION_FLOAT}>:AS_PRECISION_FLOAT>
    $<$<BOOL:${AS_PRECISION_DOUBLE}>:AS_PRECISION_DOUBLE>
    $<$<BOOL:${AS_COL_MAJOR}>:AS_COL_MAJOR>
    $<$<BOOL:${AS_ROW_MAJOR}>:AS_ROW_MAJOR>
    $<$<BOOL:${AS_COVERAGE}>:AS_COVERAGE>)
target_link_libraries(
    ${PROJECT_NAME}
    as::as Catch2::Catch2 Microsoft.GSL::GSL)

add_custom_target(scrub
    COMMAND ${CMAKE_MAKE_PROGRAM} clean
    COMMAND rm -f ${CMAKE_BINARY_DIR}/CMakeFiles/as-test.dir/*.gcno
    COMMAND rm -f ${CMAKE_BINARY_DIR}/CMakeFiles/as-test.dir/*.gcda
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    COMMENT "Clean working directory")
