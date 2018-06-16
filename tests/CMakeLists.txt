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

IF (APPLE)
    LINK_DIRECTORIES(${PROJ_EXTERNAL_PATH}/google-test/lib/macOS/x64)
ELSEIF (MSVC)
    LINK_DIRECTORIES(${PROJ_EXTERNAL_PATH}/google-test/lib/windows/msvc/x64)
ELSEIF (MINGW)
    LINK_DIRECTORIES(${PROJ_EXTERNAL_PATH}/google-test/lib/windows/gcc/x64)
ENDIF ()

ADD_EXECUTABLE(${PROJ_NAME} ${PROJ_SOURCE})

TARGET_INCLUDE_DIRECTORIES(${PROJ_NAME}
    PRIVATE ${PROJ_INCLUDE_DIR}
    PRIVATE ${PROJ_EXTERNAL_PATH}/google-test/include
    PRIVATE ${PROJ_EXTERNAL_PATH}/glm)

TARGET_LINK_LIBRARIES("${PROJ_NAME}" "${PROJ_LIBS}")