# Percolation Simulation

A 2D bernoulli site-percolation simulation written in C++.  
Supported features include:
- Square, hexagonal, and triangular lattice geometries
- BFS percolation check, cluster labelling, and largest non-spanning cluster identifier
- Parameter sweep application (get_percolation_results) which calculates percentage percolated and average largest cluster for each configuration
- Plotting of results within a jupyter notebook

Includes CMake support and CLI11 implementation.

## Building The Project

### Prerequisites
You will need:
- a C++ compiler
- CMake 3.2+

First we need to check out the git repo:
```bash
❯ cd your-workspace
❯ git clone https://github.com/ethanmort/percolation-simulation.git
❯ cd percolation-simulation
```
Then to build the project from source,
```bash
❯ cmake -B build
❯ cmake --build build --config Release
```

## Usage

```bash
❯ ./bin/get_percolation_results <parameters>
```
To see what parameters are available:
```bash
❯ ./bin/get_percolation_results --help
```
By default, results file is `/output/percolation_results.csv`. Filename or path can be set using `--output-file`.

## Visualisation
To view results, `/notebooks/plot_results.ipynb` can be used to plot the the curves of percentage percolated and average largest cluster against $p$.

