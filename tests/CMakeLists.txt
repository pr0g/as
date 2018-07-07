cmake_minimum_required(VERSION 3.11.4)

set(PROJ_NAME "as-tests")

project(${PROJ_NAME} CXX)

set(PROJ_INCLUDE_DIR ${PROJ_SRC_PATH}
                     ${CMAKE_SOURCE_DIR})

set(PROJ_SOURCE ${PROJ_TEST_PATH}/main.cpp
                ${PROJ_TEST_PATH}/as-math-output.hpp
                ${PROJ_TEST_PATH}/test-vec.cpp
                ${PROJ_TEST_PATH}/test-mat.cpp
                ${PROJ_TEST_PATH}/test-point.cpp
                ${PROJ_TEST_PATH}/test-quat.cpp
                ${PROJ_TEST_PATH}/test-affine.cpp)

set(PROJ_LIBS gtest_main gtest as)

if (APPLE)
    link_directories(${PROJ_EXTERNAL_PATH}/google-test/lib/macOS/x64)
elseif (MSVC)
    link_directories(${PROJ_EXTERNAL_PATH}/google-test/lib/windows/msvc/x64)
elseif (MINGW)
    link_directories(${PROJ_EXTERNAL_PATH}/google-test/lib/windows/gcc/x64)
endif ()

add_executable(${PROJ_NAME} ${PROJ_SOURCE})

target_include_directories(${PROJ_NAME}
    PRIVATE ${PROJ_INCLUDE_DIR}
    PRIVATE ${PROJ_EXTERNAL_PATH}/google-test/include
    PRIVATE ${PROJ_EXTERNAL_PATH}/glm)

target_link_libraries("${PROJ_NAME}" "${PROJ_LIBS}")