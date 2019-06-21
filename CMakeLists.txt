cmake_minimum_required(VERSION 3.8)

project(as VERSION 0.0.1 LANGUAGES CXX)

add_library(as INTERFACE)

include(GNUInstallDirs)

target_include_directories(
    as INTERFACE
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>)

target_compile_features(
    as INTERFACE cxx_std_14)

install(
    TARGETS as
    EXPORT as-config)

install(
    EXPORT as-config
    NAMESPACE as::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/as)

install(
    DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/include/as/
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/as)
