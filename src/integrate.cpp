//#include <cstdlib>
#include <fstream>
#include <iterator>
#include <vector>
#include "nbody.hpp"
#include "nbody_rk4.hpp"

/*
 * TODO:
 *     parse input file / arguments
 */

const int MAX_LINE_LEN = 256;
const int MAX_ELEM_LEN = 32;

int main(int argc, char *argv[]) {
    // TODO: Let user choose filename
    std::ifstream infile("params");
    std::vector<double> params((std::istream_iterator<double>(infile)),
                                std::istream_iterator<double>());

    // Get number of bodies and number of dimensions
    int n_bodies = (int) params[0];
    int n_dims = (int) params[1];

    double m[n_bodies];
    double x_init[2 * n_dims * n_bodies];
    // Get masses, positions and velocities
    for (int i = 0; i < n_bodies; i++) {
        m[i] = params[2 + i * (2 * n_dims + 1)];
        for (int j = 0; j < 2 * n_dims; j++) {
            x_init[i * (2 * n_dims) + j] =
                params[2 + i * (2 * n_dims + 1) + j + 1];
        }
    }

    NBodyRK4 system = NBodyRK4(n_bodies, n_dims, m, 0.0, x_init, false, NULL);
    system.integrate(10.0, 1e-6, 1e-6);

    return 0;
}
