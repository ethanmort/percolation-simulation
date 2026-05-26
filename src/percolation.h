/**
 * Implimentation of classical percolation model
 */

struct Square {
    int r;
    int c;
    int val;
    struct Square *neighbours[4];
};

class Lattice {
    double p;
    int height;
    int width;
    Square **sites;
    bool percolates;
    void connectNeighbours() const;
    bool checkPercolation(bool);

    public:
        Lattice(double p, int size);
        ~Lattice();
        bool doesPercolate() const;
}

int chance(double p);