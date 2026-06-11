cmake_minimum_required(VERSION 4.3)

project(PercolationSimulation)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(apps)

add_subdirectory(src)

add_library(CLI11 INTERFACE)

target_include_directories(CLI11
    INTERFACE
        extern
)
