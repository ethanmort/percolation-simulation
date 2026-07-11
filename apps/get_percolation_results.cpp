/*
 *  Example use case of percolation model.
 *  For varying p, heights, and widths, simulates lattices and calculates:
 *      - percetange percolated
 *      - average size of maximum non-spanning cluster
 *
 *  Output: `percolation_results.csv`, which can then be plotted within `plot_results.ipynb`
 */

#include "percolation.hpp"
#include "CLI11.hpp"

#include <iostream>
#include <fstream>
#include <iomanip>
#include <filesystem>

#ifndef OUTPUT_DIR
#error "OUTPUT_DIR is not defined. It needs to be set using target_compile_defintions() in apps/CMakeLists.txt"
#endif

template <typename T>
requires std::integral<T> || std::floating_point<T>
struct Sweep {
    T min;
    T max;
    T step;
};

template <typename T>
void validate_input_logic(const Sweep<T> &param, const std::string param_name, CLI::App &app);

template <GeometryType Geometry>
void run_lattice_sweep(const std::string &geometry, const int &n_repeats, const Sweep<int> &h, const Sweep<int> &w, const Sweep<double> &p, std::ofstream &results);

int main(int argc, char *argv[])
{
    // Parse user input
    CLI::App app;

    std::vector<std::string> geometries;
    app.add_option("--geometry", geometries, "Lattice geometry (square, hex)")
        ->expected(1,2)
        ->check(CLI::IsMember({"square", "hex"}))
        ->required();

    int n_repeats = 1000;
    app.add_option("--n-repeats", n_repeats, "Number of repeats for each value of p")
        ->check(CLI::PositiveNumber);

    double p_single;
    Sweep<double> p;
    app.add_option("--p", p_single, "Value of p")
        ->check(CLI::Range(0.0,1.0));
    app.add_option("--p-min", p.min, "Minimum value of p")
        ->check(CLI::Range(0.0,1.0));
    app.add_option("--p-max", p.max, "Maximum value of p")
        ->check(CLI::Range(0.0,1.0));
    app.add_option("--p-step", p.step, "Step in p")
        ->check(CLI::PositiveNumber);

    int h_single;
    Sweep<int> h;
    app.add_option("--h", h_single, "Single height value")
        ->check(CLI::PositiveNumber);
    app.add_option("--h-min", h.min, "Minimum height")
        ->check(CLI::PositiveNumber);
    app.add_option("--h-max", h.max, "Maximum height")
        ->check(CLI::PositiveNumber);
    app.add_option("--h-step", h.step, "Step in height")
        ->check(CLI::PositiveNumber);
    
    int w_single;
    Sweep<int> w;
    app.add_option("--w", w_single, "Width")
        ->check(CLI::PositiveNumber);
    app.add_option("--w-min", w.min, "Minimum width")
        ->check(CLI::PositiveNumber);
    app.add_option("--w-max", w.max, "Maximum width")
        ->check(CLI::PositiveNumber);
    app.add_option("--w-step", w.step, "Step in width")
        ->check(CLI::PositiveNumber);
    
    std::string output_name = "percolation_results.csv";
    app.add_option("--output-file", output_name, "Output name");

    CLI11_PARSE(app, argc, argv);

    if (app.count("--p") == 1) {p.min=p.max=p_single;p.step=1;};
    if (app.count("--h") == 1) {h.min=h.max=h_single;h.step=1;};
    if (app.count("--w") == 1) {w.min=w.max=w_single;w.step=1;};


    try {
        validate_input_logic(p, "p", app);
        validate_input_logic(h, "h", app);
        validate_input_logic(w, "w", app);

        if (geometries.size() == 2 && geometries[0] == geometries[1]) {
            throw CLI::ValidationError("--geometry", "Duplicate geometries specified");
        }
    } catch (const CLI::ParseError &e) {
        return app.exit(e);
    }

    // Output results
    std::filesystem::path output_path = std::filesystem::path(OUTPUT_DIR) / output_name; // if output_name is absolute, output_path = output_name.
    std::filesystem::create_directories(output_path.parent_path()); // Creates output directory if it doesnt exist
    std::ofstream Results(output_path); //

    Results << "geometry,h,w,p,chance,max_cluster\n";
    Results << std::fixed << std::setprecision(6);
    
    for (std::string &geometry : geometries) {
        if (geometry == "square") {
            run_lattice_sweep<Square>(geometry, n_repeats, h, w, p, Results);
        } else if (geometry == "hex") {
            run_lattice_sweep<Hex>(geometry, n_repeats, h, w, p, Results);
        }
    }

    return 0;
}

template <typename T>
void validate_input_logic(const Sweep<T> &param, const std::string param_name, CLI::App &app)
{
    bool specified_as_range =
        app.count("--"+param_name+"-min") == 1 && 
        app.count("--"+param_name+"-max") == 1 &&
        app.count("--"+param_name+"-step") == 1;
    
    bool specified_as_single =
        app.count("--"+param_name) == 1;

    if (!specified_as_range && !specified_as_single) {
        throw CLI::ValidationError(
            "--" + param_name,
            "Must provide either --" + param_name +
            " or --" + param_name + "-min, --" + 
            param_name + "-max and --" + param_name + "-step"
        );
    } else if (specified_as_range && specified_as_single) {
        throw CLI::ValidationError(
            "--" + param_name,
            "Cannot provide both --" + param_name +
            " and --" + param_name + "-min/max/step"
        );
    }
    
    if (param.min > param.max) {
        throw CLI::ValidationError(
            "--" + param_name + "-min", 
            "--" + param_name + "-min cannot be greater than --" + param_name + "-max"
        );
    }

}

template <GeometryType Geometry>
void run_lattice_sweep(const std::string &geometry, const int &n_repeats, const Sweep<int> &h, const Sweep<int> &w, const Sweep<double> &p, std::ofstream &results)
{
    for (int h_value = h.min; h_value <= h.max; h_value+=h.step) {
        for (int w_value = w.min; w_value <= w.max; w_value+=w.step) {
            for (double p_value = p.min; p_value <= p.max; p_value+=p.step) {
                int percolate_count = 0;
                int max_cluster_sum = 0;
                for (int trial = 0; trial < n_repeats; trial++) {
                    Lattice<Geometry> lat(p_value, h_value, w_value);
                    if (lat.doesPercolate()) percolate_count++;
                    max_cluster_sum += lat.getMaxCluster();
                }
                results 
                    << geometry << "," << h_value << "," << w_value << "," << p_value << "," 
                    << (double)percolate_count/n_repeats << "," << (double)max_cluster_sum/n_repeats << "\n";
            }
        }
    }
}