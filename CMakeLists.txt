cmake_minimum_required(VERSION 3.2)

project(PercolationSimulation)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

add_subdirectory(apps)

add_subdirectory(src)

add_library(CLI11 INTERFACE)

target_include_directories(CLI11
    INTERFACE
        extern
)
