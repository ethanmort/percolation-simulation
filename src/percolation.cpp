#include <iostream>
#include <random>
#include <vector>
#include <queue>

#include "percolation.h"

Square::Square(int r, int c) {
    this->r = r;
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

    percolates = false;
    checkPercolation();
}

/// Set pointers to neighbouring sites
void Lattice::connectNeighbours()
{
    for(int j = 0; j < height; j++) {
        for(int i = 0; i < width; i++) {
            // If neighbour out of bounds, then set to nullptr
            sites[j][i].neighbours[0] = (j+1 < height)  ? &sites[j+1][i] : nullptr;
            sites[j][i].neighbours[1] = (i+1 < width)   ? &sites[j][i+1] : nullptr;
            sites[j][i].neighbours[2] = (j > 0)       ? &sites[j-1][i] : nullptr;
            sites[j][i].neighbours[3] = (i > 0)       ? &sites[j][i-1] : nullptr;
        }
    }
}

Lattice::~Lattice()
{
    for (int j = 0; j < height; j++) {
        delete [] sites[j];
    }

    delete [] sites;
}

/// Returns 1 with chance p and 0 with chance 1-p
int chance(double p)
{
    if (rand()/(double)RAND_MAX < p) return 1;
    return 0;
}

void Lattice::checkPercolation()
{
    std::vector<std::vector<bool>> visited(height, std::vector<bool>(width,false));

    std::queue<std::pair<int,int>> to_visit;

    for (int j = 0; j < height; j++) {
        for (int i = 0; i < width; i++) {
            if (visited[j][i] || sites[j][i].val == 0) continue;
            to_visit.push({j,i});
            visited[j][i] = true;         
            int r_min = j;
            int r_max = j;
            int c_min = i;
            int c_max = i;

            while (!to_visit.empty()) {

                auto[r,c] = to_visit.front();
                to_visit.pop();

                Square &site = sites[r][c];

                for (Square *neighbour : site.neighbours) {
                    if (neighbour && neighbour->val == 1 && !visited[neighbour->r][neighbour->c]) {
                        visited[neighbour->r][neighbour->c] = true;
                        to_visit.push({neighbour->r, neighbour->c});
                        r_min = std::min(neighbour->r, r_min);
                        r_max = std::max(neighbour->r, r_max);
                        c_min = std::min(neighbour->c, c_min);
                        c_max = std::max(neighbour->c, c_max);
                    }
                }
            }
            if (
                    (r_min == 0 && r_max == height - 1) || 
                    (c_min == 0 && c_max == width - 1)
                ) {
                    percolates = true;
                    return;
                }
        }
    }

    percolates = false;
    return;
}

bool Lattice::doesPercolate() const
{
    return percolates;
}