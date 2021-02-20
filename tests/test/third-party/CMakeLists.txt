cmake_minimum_required(VERSION 3.15)

project(third-party)

include(ExternalProject)

get_property(isMultiConfig GLOBAL PROPERTY GENERATOR_IS_MULTI_CONFIG)
if (NOT isMultiConfig)
    if(NOT CMAKE_BUILD_TYPE)
        set(CMAKE_BUILD_TYPE Debug CACHE STRING "" FORCE)
    endif()
    set(build_type_dir ${CMAKE_BUILD_TYPE})
    set(build_type_arg -DCMAKE_BUILD_TYPE=$<CONFIG>)
endif()

ExternalProject_Add(
    gsl
    GIT_REPOSITORY https://github.com/microsoft/GSL.git
    GIT_TAG        origin/main
    GIT_SHALLOW    1
    BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR}/gsl/build/${build_type_dir}
    INSTALL_DIR ${CMAKE_CURRENT_BINARY_DIR}
    CMAKE_ARGS ${build_type_arg}
               -D CMAKE_INSTALL_PREFIX=<INSTALL_DIR>
               -D GSL_INSTALL=ON
               -D GSL_TEST=OFF)

ExternalProject_Add(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG        origin/devel
    GIT_SHALLOW    1
    BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR}/Catch2/build/${build_type_dir}
    INSTALL_DIR ${CMAKE_CURRENT_BINARY_DIR}
    CMAKE_ARGS ${build_type_arg}
               -D CMAKE_INSTALL_PREFIX=<INSTALL_DIR>
               -D CATCH_BUILD_TESTING=OFF)
