#ifndef LATTICE_TPP
#define LATTICE_TPP

#include "percolation.h"

#include <vector>
#include <queue>

template <typename Geometry>
Lattice<Geometry>::Lattice(double p,  int height, int width)
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
    max_cluster_size = 0;
    analyse();
}

template <typename Geometry>
void Lattice<Geometry>::analyse()
{
    std::vector<std::vector<bool>> visited(height, std::vector<bool>(width,false));

    std::queue<std::pair<int,int>> to_visit;

    int cluster_number = 0;

    for (int j = 0; j < height; j++) {
        for (int i = 0; i < width; i++) {
            if (visited[j][i] || !sites[j][i].occupied) continue;
            to_visit.push({j,i});
            visited[j][i] = true;
            int cluster_size = 0;
            int r_min = j;
            int r_max = j;
            int c_min = i;
            int c_max = i;

            while (!to_visit.empty()) {
                auto[r,c] = to_visit.front();
                to_visit.pop();

                sites[r][c].cluster = cluster_number;
                cluster_size++;

                for (int k = 0; k < Geometry::neighbour_count; k++) {
                    int nr = r + Geometry::dr(r,k);
                    int nc = c + Geometry::dc(r,k);

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
            } else if (cluster_size > max_cluster_size) {
                max_cluster_size = cluster_size;
            }
            cluster_number++;
        }
    }
    return;
}

template <typename Geometry>
bool Lattice<Geometry>::doesPercolate() const
{
    return percolates;
}

template <typename Geometry>
int Lattice<Geometry>::getMaxCluster() const
{
    return max_cluster_size;
}

#endif
