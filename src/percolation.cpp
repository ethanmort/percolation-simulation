#include "percolation.h"

#include <random>
#include <vector>
#include <queue>


/// Initialise lattice values and allocate memory for sites
Lattice::Lattice(double p,  int height, int width)
{
    this->p = p;
    this->height = height;
    this->width = width;

    sites = std::vector<std::vector<Site>>(height, std::vector<Site>(width));

    for(int j = 0; j < height; j++) {
        for(int i = 0; i < width; i++) {
            sites[j][i].occupied = chance(p);
        }
    }

    percolates = false;
    checkPercolation();
}

/// Returns 1 with chance p and 0 with chance 1-p
bool chance(double p)
{
    if (rand()/(double)RAND_MAX < p) return true;
    return false;
}

// Check for percolation
void Lattice::checkPercolation()
{
    std::vector<std::vector<bool>> visited(height, std::vector<bool>(width,false));

    std::queue<std::pair<int,int>> to_visit;

    for (int j = 0; j < height; j++) {
        for (int i = 0; i < width; i++) {
            if (visited[j][i] || !sites[j][i].occupied) continue;
            to_visit.push({j,i});
            visited[j][i] = true;
            int r_min = j;
            int r_max = j;
            int c_min = i;
            int c_max = i;

            while (!to_visit.empty()) {
                auto[r,c] = to_visit.front();
                to_visit.pop();
                
                const int dr[4] = {1, 0, -1, 0};
                const int dc[4] = {0, 1, 0, -1};

                for (int k = 0; k < 4; k++) {
                    int nr = r + dr[k];
                    int nc = c + dc[k];

                    if (nr >= height || nr < 0 ||
                        nc >= width || nc < 0)
                    {
                        continue;
                    }

                    if (sites[nr][nc].occupied && !visited[nr][nc]) {
                        visited[nr][nc] = true;
                        to_visit.push({nr,nc});
                        r_min = std::min(nr,r_min);
                        r_max = std::max(nr,r_max);
                        c_min = std::min(nc,c_min);
                        c_max = std::max(nc,c_max);
                    }
                }
            }
            
            if ((r_min == 0 && r_max == height-1) || (c_min == 0 && c_max == width-1)) {
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