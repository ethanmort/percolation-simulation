add_library(Percolation)

target_sources(Percolation
    PRIVATE
        percolation.cpp
    PUBLIC
        FILE_SET HEADERS
        FILES
            percolation.hpp
)