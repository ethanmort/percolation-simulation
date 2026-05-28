#include <iostream>
#include <random>

#include "percolation.h"

Square::Square(int r, int c) {
    this->r = c;
    this->c = c;
}

/// Initialise lattice values and allocate memory for sites
Lattice::Lattice(double p,  int height, int width)
{
    this->p = p;
    this->height = height;
    this->width = width;

    sites = new Square *[height];
    for(int j = 0; j < height; j++) {
        sites[j] = new Square[width];
    }

    for(int j = 0; j < height; j++) {
        for(int i = 0; i < width; i++) {
            sites[j][i].r = j;
            sites[j][i].c = i;
            sites[j][i].val = chance(p);
        }
    }

    connectNeighbours();
}

/// Set pointers to neighbouring sites
void Lattice::connectNeighbours()
{
    for(int j = 0; j < height; j++) {
        for(int i = 0; i < width; i++) {
            sites[j][i].neighbours[0] = (j+1 < height)  ? &sites[j+1][i] : nullptr; // If neighbour out of bounds, then set to nullptr
            sites[j][i].neighbours[1] = (i+1 < width)   ? &sites[j][i+1] : nullptr;
            sites[j][i].neighbours[2] = (j-1 > 0)       ? &sites[j-1][i] : nullptr;
            sites[j][i].neighbours[3] = (i-1 > 0)       ? &sites[j][i-1] : nullptr;
        }
    }
}

int chance(double p)
{
    if (rand()/(double)RAND_MAX < p) return 1;
    return 0;
}