/**
 *  Example use case of percolation model.
 *  For varying p, simulates lattices and calculates:
 *      - percetange percolated
 *      - maximum non-spanning cluster
 *
 *  Output: `percolation_results.csv`, which can then be plotted within `plot_results.ipynb`
 */

#include "percolation.h"

#include <iostream>
#include <fstream>
#include <iomanip>

#define N_REPEATS 1000

int main(void)
{
    std::ofstream OutFile("percolation_results.csv");

    OutFile << "p,chance,max_cluster\n";
    OutFile << std::fixed << std::setprecision(6);
    
    for (double p = 0; p < 1; p+=0.01) {
        int percolate_count = 0;
        int max_cluster_count = 0;
        for (int n = 0; n < N_REPEATS; n++) {
            Lattice<Square> lat(p, 20, 20);
            if (lat.doesPercolate()) percolate_count++;
            max_cluster_count += lat.getMaxCluster();
        }
        OutFile << p << "," << (double)percolate_count/N_REPEATS << "," << (double)max_cluster_count/N_REPEATS << "\n";
    }

    return 0;
}