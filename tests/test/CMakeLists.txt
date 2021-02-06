cmake_minimum_required(VERSION 3.15)

project(
    as-test
    VERSION 0.0.1
    LANGUAGES CXX)

include(FetchContent)

FetchContent_Declare(
    as
    SOURCE_DIR ../../../)
FetchContent_MakeAvailable(as)

find_package(Catch2 CONFIG REQUIRED)
find_package(Microsoft.GSL CONFIG REQUIRED)

add_executable(
    ${PROJECT_NAME}
    as-affine.test.cpp
    as-mat.test.cpp
    as-quat.test.cpp
    as-vec.test.cpp
    as-math.test.cpp
    as-view.test.cpp
    as-rigid.test.cpp)

# cmake-format: off
string(
    APPEND
    coverage_options
    "$<"
        "$<AND:"
            "$<COMPILE_LANGUAGE:CXX>,"
            "$<CXX_COMPILER_ID:GNU>,"
            "$<BOOL:${AS_COVERAGE}>"
        ">:"
        "{options}"
    ">")
# cmake-format: on

string(REPLACE "{options}" "-coverage;-g;-O0;-fno-inline;" # gcov
               compile_options "${coverage_options}")

string(REPLACE "{options}" "-coverage;" # gcc
               link_options "${coverage_options}")

# cmake-format: off
string(
    APPEND
    compile_options
    "$<"
        "$<AND:"
            "$<COMPILE_LANGUAGE:CXX>,"
            "$<OR:"
                "$<CXX_COMPILER_ID:Clang>,"
                "$<CXX_COMPILER_ID:AppleClang>"
            ">"
        ">:"
        "-Weverything;-Wno-c++98-compat;-Wno-;-Wno-global-constructors;-Wno-;"
        "-Wno-c++98-compat-pedantic;-Wno-"
    ">"
    "$<"
        "$<AND:"
            "$<COMPILE_LANGUAGE:CXX>,"
            "$<CXX_COMPILER_ID:MSVC>"
        ">:"
        "/W4;/WX;/permissive-;/w14640;/w14242;/w14254;/w14263;/w14265;/w14287;"
        "/we4289;/w14296;/w14311;/w14545;/w14546;/w14547;/w14549;/w14555;"
        "/w14619;/w14640;/w14826;/w14928;/w14800"
    ">"
    "$<"
        "$<AND:"
            "$<COMPILE_LANGUAGE:CXX>,"
            "$<CXX_COMPILER_ID:GNU>"
        ">:"
        "-Wall;-Wextra;-Wshadow;-Wnon-virtual-dtor;-Wpedantic;-Wold-style-cast;"
        "-Wcast-align;-Wunused;-Wconversion;-Wsign-conversion;"
        "-Wmisleading-indentation;-Wduplicated-cond;-Wduplicated-branches;"
        "-Wlogical-op;-Wnull-dereference;-Wdouble-promotion;-Wuseless-cast"
    ">")
# cmake-format: on

target_compile_options(${CMAKE_PROJECT_NAME} PRIVATE "${compile_options}")
target_link_options(${CMAKE_PROJECT_NAME} PRIVATE "${link_options}")
set_target_properties(
    ${PROJECT_NAME} PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED YES
                               CXX_EXTENSIONS NO NO_SYSTEM_FROM_IMPORTED false)
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)
target_compile_definitions(
    ${PROJECT_NAME}
    PRIVATE $<$<BOOL:${AS_PRECISION_FLOAT}>:AS_PRECISION_FLOAT>
            $<$<BOOL:${AS_PRECISION_DOUBLE}>:AS_PRECISION_DOUBLE>
            $<$<BOOL:${AS_COL_MAJOR}>:AS_COL_MAJOR>
            $<$<BOOL:${AS_ROW_MAJOR}>:AS_ROW_MAJOR>
            $<$<BOOL:${AS_COVERAGE}>:AS_COVERAGE>)
target_link_libraries(
    ${PROJECT_NAME} as Catch2::Catch2WithMain Microsoft.GSL::GSL)

include(CTest)
include(Catch)
catch_discover_tests(${PROJECT_NAME})

add_custom_target(
    scrub
    COMMAND ${CMAKE_MAKE_PROGRAM} clean
    COMMAND rm -f ${CMAKE_BINARY_DIR}/CMakeFiles/as-test.dir/*.gcno
    COMMAND rm -f ${CMAKE_BINARY_DIR}/CMakeFiles/as-test.dir/*.gcda
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    COMMENT "Clean working directory")
