/**
 * Implimentation of square 2D classical percolation model
 */

#ifndef PERCOLATION_H
#define PERCOLATION_H

#include <vector>

struct Site {
    bool occupied = false;
    int cluster =  -1;
};

class Lattice {
    double p;
    int height;
    int width;
    std::vector<std::vector<Site>> sites;

    bool percolates;
    int max_cluster_size; // largest cluster excluding spanning clusters

    /// Check for percolation, label clusters, and find largest cluster size
    void analyse();

    public:
        Lattice(double p, int height, int width);
        bool doesPercolate() const;
        int getMaxCluster() const;
};

/// Return true with chance p and false with chance 1-p
bool chance(double p);

#endif