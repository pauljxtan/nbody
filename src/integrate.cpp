#include <getopt.h>
#include <cstring>
#include <fstream>
#include <iostream>
#include <iterator>
#include <vector>
#include "integrate.hpp"
#include "nbody.hpp"
#include "nbody_rk4.hpp"

const int MAX_FILENAME_LEN = 128;
// Number of parameters in first row of parameter file
// (i.e. everything before state vectors)
const int PARAM_IDX_SKIP = 5;

int main(int argc, char *argv[]) {
    bool write = false;
    char infilename[MAX_FILENAME_LEN], outfilename[MAX_FILENAME_LEN];
    int c, n_bodies, n_dims;
    double delta, duration, dt_init;
    FILE * p_outfile = NULL;

    // Parse arguments
    if (argc < 2) {
        print_usage();
        return 1;
    }

    opterr = 0;
    while ((c = getopt(argc, argv, "p:w:")) != EOF) {
        switch (c) {
            case 'p':
                std::strcpy(infilename, optarg);
                break;
            case 'w':
                write = true;
                std::strcpy(outfilename, optarg);
                break;
            default:
                print_usage();
                return 1;
        }
    }

    // Parse the parameter file
    std::ifstream infile(infilename);
    std::vector<double> params((std::istream_iterator<double>(infile)),
                                std::istream_iterator<double>());

    // Get number of bodies
    n_bodies = (int) params[0];
    // Get number of dimensions
    n_dims = (int) params[1];
    // Get integration duration
    duration = params[2];
    // Get initial time step
    dt_init = params[3];
    // Get desired accuracy
    delta = params[4];

    // Get masses, positions and velocities
    double m[n_bodies];
    double x_init[2 * n_dims * n_bodies];
    for (int i = 0; i < n_bodies; i++) {
        m[i] = params[PARAM_IDX_SKIP + i * (2 * n_dims + 1)];
        for (int j = 0; j < 2 * n_dims; j++)
            x_init[i * (2 * n_dims) + j] =
                params[PARAM_IDX_SKIP + i * (2 * n_dims + 1) + j + 1];
    }

    if (write) p_outfile = fopen(outfilename, "w");

    // Initialize the integrator
    NBodyRK4 system = NBodyRK4(n_bodies, n_dims, m, x_init, write, p_outfile);
    // Begin the simulation
    system.integrate(duration, dt_init, delta);

    if (write) fclose(p_outfile);

    return 0;
}

void print_usage() {
    std::cout << "Usage: integrate -p filename [-w filename]\n";
}
