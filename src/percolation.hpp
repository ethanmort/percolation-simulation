/**
 * Implementation of 2D classical percolation model
 */

#ifndef PERCOLATION_H
#define PERCOLATION_H

#include <vector>

/// Triangular lattice morphology
class Triangle {
    public:
        static constexpr int neighbour_count = 6;

        static int dr(int r, int c, int k);
        static int dc(int r, int c, int k);
};

/// Square lattice morphology
class Square {
    public:
        static constexpr int neighbour_count = 4;

        /// Change in row and column values between site and neighbours
        static int dr(int r, int c, int k);
        static int dc(int r, int c, int k);
};

/// Hexagonal lattice morphology
class Hex {
    public:
        static constexpr int neighbour_count = 3;
        
        static int dr(int r, int c, int k);
        static int dc(int r, int c, int k);
};

struct Site {
    bool occupied = false;
    int cluster =  -1;
};

template <typename G>
concept GeometryType = requires(int r, int c, int k)
{
    { G::dr(r, c, k) } -> std::convertible_to<int>;
    { G::dc(r, c, k) } -> std::convertible_to<int>;
    { G::neighbour_count } -> std::convertible_to<int>;
};

template <GeometryType Geometry>
class Lattice {
    double p;
    int height;
    int width;
    std::vector<std::vector<Site>> sites;

    bool percolates;
    int max_cluster_size; // size of largest non spanning cluster

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