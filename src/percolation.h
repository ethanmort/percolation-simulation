/**
 * Implimentation of square 2D classical percolation model
 */

struct Square {
    int r;
    int c;
    int val;
    struct Square *neighbours[4];
    Square(int j = 0, int i = 0);
};

class Lattice {
    double p;
    int height;
    int width;
    Square **sites;
    bool percolates;
    void connectNeighbours();
    void checkPercolation(); // To be implimented

    public:
        Lattice(double p, int rows, int cols);
        ~Lattice();
        bool doesPercolate() const; // To be implimented
};

int chance(double p);