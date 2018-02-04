CMAKE_MINIMUM_REQUIRED(VERSION 3.4)

SET(PROJ_NAME "as-tests")

PROJECT(${PROJ_NAME} CXX)

SET(PROJ_INCLUDE_DIR ${PROJ_SRC_PATH}
                     ${CMAKE_SOURCE_DIR})

SET(PROJ_SOURCE ${PROJ_TEST_PATH}/main.cpp
                ${PROJ_TEST_PATH}/as-math-output.hpp
                ${PROJ_TEST_PATH}/test-vec.cpp
                ${PROJ_TEST_PATH}/test-mat.cpp
                ${PROJ_TEST_PATH}/test-point.cpp
                ${PROJ_TEST_PATH}/test-quat.cpp
                ${PROJ_TEST_PATH}/test-affine.cpp)

SET(PROJ_LIBS gtest_main gtest as)

INCLUDE_DIRECTORIES(${PROJ_INCLUDE_DIR} ${PROJ_EXTERNAL_PATH}/google-test/include
                                        ${PROJ_EXTERNAL_PATH}/glm)

if (APPLE)
    #-DCMAKE_OSX_ARCHITECTURES=x86_64
    LINK_DIRECTORIES(${PROJ_EXTERNAL_PATH}/google-test/lib/macOS/x64)
elseif(MSVC)
    LINK_DIRECTORIES(${PROJ_EXTERNAL_PATH}/google-test/lib/windows/msvc/x64)
elseif(MINGW)
    LINK_DIRECTORIES(${PROJ_EXTERNAL_PATH}/google-test/lib/windows/gcc/x64)
endif(APPLE)

ADD_EXECUTABLE(${PROJ_NAME} ${PROJ_SOURCE})

if (CMAKE_COMPILER_IS_GNUCXX)
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wno-long-long")
endif(CMAKE_COMPILER_IS_GNUCXX)

SET_PROPERTY(TARGET ${PROJ_NAME} PROPERTY CXX_STANDARD 14)
SET_PROPERTY(TARGET ${PROJ_NAME} PROPERTY C_STANDARD 99)

TARGET_LINK_LIBRARIES("${PROJ_NAME}" "${PROJ_LIBS}")