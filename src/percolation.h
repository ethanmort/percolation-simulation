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

    void checkPercolation();
    std::vector<std::pair<int,int>> getNeighbours(int r, int c) const;

    public:
        Lattice(double p, int height, int width);
        bool doesPercolate() const;
};

bool chance(double p);

#endif