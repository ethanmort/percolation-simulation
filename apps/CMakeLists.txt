add_executable(get_percolation_results)

target_sources(get_percolation_results
    PRIVATE
        get_percolation_results.cpp
)

target_link_libraries(get_percolation_results
    PRIVATE
        CLI11
        Percolation
)

target_compile_definitions(get_percolation_results
    PRIVATE
        OUTPUT_DIR="${CMAKE_SOURCE_DIR}/output/"
)