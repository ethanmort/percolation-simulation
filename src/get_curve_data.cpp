#include <iostream>
#include <fstream>
#include <iomanip>

#include "percolation.h"

#define N_REPEATS 10000

int main(void)
{
    std::ofstream OutFile("output.csv");

    OutFile << "p,chance\n";
    OutFile << std::fixed << std::setprecision(6);
    
    for (double p = 0; p < 1; p+=0.01) {
        int percolate_count = 0;
        for (int n = 0; n < N_REPEATS; n++) {
            Lattice lat(p, 20, 20);
            if (lat.doesPercolate()) percolate_count++;
        }
        OutFile << p << "," << (double)percolate_count/N_REPEATS << "\n";
    }

    return 0;
}