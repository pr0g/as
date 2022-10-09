cmake_minimum_required(VERSION 3.15)

project(
    as
    VERSION 1.0.0
    LANGUAGES CXX)

include(FetchContent)

FetchContent_Declare(
    cmake-helpers
    GIT_REPOSITORY https://github.com/pr0g/cmake-helpers.git
    GIT_TAG 7e1ded2f027dd2bd3265ab7cb4972d06083fbcc5)

FetchContent_MakeAvailable(cmake-helpers)
list(APPEND CMAKE_MODULE_PATH ${cmake-helpers_SOURCE_DIR})

add_library(${PROJECT_NAME} INTERFACE)
target_include_directories(
    ${PROJECT_NAME}
    INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>)
target_compile_features(${PROJECT_NAME} INTERFACE cxx_std_17)

include(thh-install)
thh_install_header_only_no_dependencies(${PROJECT_NAME})
