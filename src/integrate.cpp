#include <cmath>
#include <iostream>
#include <valarray>
#include "nbody.hpp"
#include "nbody_rk4.hpp"

/*
 * TODO:
 *     parse input file / arguments
 */

int main(int argc, char *argv[]) {
    // masses
    //double m[] = {1.0, 0.1};
    double m[] = {150.0, 200.0, 250.0};

    // positions and velocities
    //double x_init[] = {0.0, 1.0, 0.0, 0.0,  0.02, 0.0,
    //                   5.0, 0.0, 0.0, 0.0, -0.2,  0.0};
    double x_init[] = { 3.0,  1.0, 0.0, 0.0, 0.0, 0.0,
                       -1.0, -2.0, 0.0, 0.0, 0.0, 0.0,
                       -1.0,  1.0, 0.0, 0.0, 0.0, 0.0};

    NBodyRK4 system = NBodyRK4(3, 3, m, 1e-5, 0.0, x_init, false, NULL);
    system.integrate(2e5);

    return 0;
}
