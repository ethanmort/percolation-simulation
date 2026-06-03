/**
 * Implementation of 2D classical percolation model
 */

#ifndef PERCOLATION_H
#define PERCOLATION_H

#include <vector>

/// Square lattice morphology
class Square
{
    public:
        static constexpr int neighbour_count = 4;

        /// Change in row and column values between site and neighbours
        static int dr(int r, int k);
        static int dc(int r, int k);
};

/// Hexagonal lattice morphology
class Hex
{
    public:
        static constexpr int neighbour_count = 6;
        static int dr(int r, int k);
        static int dc(int r, int k);
};

struct Site {
    bool occupied = false;
    int cluster =  -1;
};

template <typename Geometry>
class Lattice {
    double p;
    int height;
    int width;
    std::vector<std::vector<Site>> sites;

    bool percolates;
    int max_cluster_size; // largest non spanning clusters

    /// Check for percolation, label clusters, and find maximum cluster size
    void analyse();

    public:
        Lattice(double p, int height, int width);
        bool doesPercolate() const;
        int getMaxCluster() const;
};

/// Return true with chance p and false with chance 1-p
bool chance(double p);

#include "lattice.tpp"

#endif