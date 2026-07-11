#include "percolation.hpp"

#include <random>

int Triangle::dr(int r, int c, int k)
{
    static int dr_options_even[6] = {1,0,-1,-1,-1,0};
    static int dr_options_odd[6] = {1,1,0,-1,0,1};
    if (r % 2 == 0) return dr_options_even[k];
    return dr_options_odd[k];
}

int Triangle::dc(int r, int c, int k)
{
    static int dc_options[6] = {0,1,1,0,-1,-1};
    return dc_options[k];
}

int Square::dr(int r, int c, int k)
{
    static int dr_options[4] = {1, 0, -1, 0};
    return dr_options[k];
}

int Square::dc(int r, int c, int k)
{
    static int dc_options[4] = {0, 1, 0, -1};
    return dc_options[k];
}

int Hex::dr(int r, int c, int k)
{
    static int dr_options[3] = {-1, 0, 1};
    return dr_options[k];
}

int Hex::dc(int r, int c, int k)
{
    static int dc_options_even[3] = {0, -1, 0};
    static int dc_options_odd[3] = {0, 1, 0};
    if ((r + c) % 2) return dc_options_even[k];
    return dc_options_odd[k];
}

bool chance(double p)
{
    if (rand()/(double)RAND_MAX < p) return true;
    return false;
}
