cmake_minimum_required(VERSION 3.8)

project(as-test VERSION 0.0.1 LANGUAGES CXX)

if (NOT DEFINED DEV_LIB_DIR)
    message(
        FATAL_ERROR "Please provide the path to the library in active development.
Example: cmake -DDEV_LIB_DIR=\"path/to/library/in/development\" ..")
endif()

include(autoinstall.cmake)
install_it(${DEV_LIB_DIR})

find_package(as REQUIRED)
find_package(GTest REQUIRED)

add_executable(
    ${PROJECT_NAME}
    main.cpp test-affine.cpp
    test-mat.cpp test-point.cpp
    test-quat.cpp test-vec.cpp
    test-math.cpp)

string(
    APPEND build_options
    "$<"
        "$<AND:"
            "$<COMPILE_LANGUAGE:CXX>,"
            "$<OR:"
                "$<CXX_COMPILER_ID:Clang>,"
                "$<CXX_COMPILER_ID:AppleClang>,"
                "$<CXX_COMPILER_ID:GNU>"
            ">"
        ">:"
        "{options}"
    ">"
)

string(
    REPLACE "{options}" "-g;-fprofile-arcs;-ftest-coverage;-O0;-fno-inline"
    compile_options "${build_options}"
)

string(
    REPLACE "{options}" "-fprofile-instr-generate" # -fprofile-generate
    link_options "${build_options}"
)

target_compile_options(
    ${CMAKE_PROJECT_NAME} PRIVATE "${compile_options}")
target_link_options(
    ${CMAKE_PROJECT_NAME} PRIVATE "${link_options}")
target_compile_features(
    ${PROJECT_NAME} PRIVATE cxx_std_17)
target_compile_definitions(
    ${PROJECT_NAME} PRIVATE AS_PRECISION_FLOAT AS_COL_MAJOR)
target_link_libraries(
    ${PROJECT_NAME} as::as GTest::GTest GTest::Main)

add_custom_target(scrub
    COMMAND ${CMAKE_MAKE_PROGRAM} clean
    COMMAND rm -f ${CMAKE_BINARY_DIR}/CMakeFiles/as-test.dir/*.gcno
    COMMAND rm -f ${CMAKE_BINARY_DIR}/CMakeFiles/as-test.dir/*.gcda
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR})
