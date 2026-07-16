# Simulation
add_executable(simulation)

target_sources(simulation
    PRIVATE
        simulation.cpp
)

target_link_libraries(simulation
    PRIVATE
        CLI11
        Percolation
)

target_compile_definitions(simulation
    PRIVATE
        OUTPUT_DIR="${CMAKE_SOURCE_DIR}/output/simulation/"
)
