#include <cmath>
#include <iostream>
#include <valarray>
#include "nbody.hpp"

/*
 * TODO:
 *     parse input file / arguments
 */

int main(int argc, char *argv[]) {
    // number of bodies
    //const int n = 2;
    const int n = 3;

    // time step
    double dt = 1e-5;
    int steps = 2e5;

    // masses
    //double m[n] = {1.0, 0.1};
    double m[n] = {150.0, 200.0, 250.0};

    // positions and velocities
    //double x_init[6 * n] = {0.0, 1.0, 0.0, 0.0,  0.02, 0.0,
    //                        5.0, 0.0, 0.0, 0.0, -0.2,  0.0};
    double x_init[6 * n] = { 3.0,  1.0, 0.0, 0.0, 0.0, 0.0,
                            -1.0, -2.0, 0.0, 0.0, 0.0, 0.0,
                            -1.0,  1.0, 0.0, 0.0, 0.0, 0.0};

    std::valarray<double> x(x_init, 6 * n);
    print_array(x);
    x = rk4_integrate(x, m, n, dt, steps);

    return 0;
}

void print_array(std::valarray<double> a) {
    for (int i = 0; i < a.size() - 1; i++) {
        std::cout << a[i] << " ";
    }
    std::cout << a[a.size() - 1] << "\n";
}

double dist(std::valarray<double> a, std::valarray<double> b) {
    return sqrt(pow(b - a, 2).sum());
}

std::valarray<double> pos(std::valarray<double> x, int i) {
    return x[std::slice(i * 6, 3, 1)];
}

std::valarray<double> vel(std::valarray<double> x, int i) {
    return x[std::slice(i * 6 + 3, 3, 1)];
}

std::slice pos_sel(int i) { return std::slice(i * 6, 3, 1); }

std::slice vel_sel(int i) { return std::slice(i * 6 + 3, 3, 1); }

std::valarray<double> newton(std::valarray<double> x, double m[], int n) {
    std::valarray<double> ri(3), rj(3);
    std::valarray<double> x_dot(n * 6);

    for (int i = 0; i < n; i++) {
        ri = pos(x, i);
        x_dot[pos_sel(i)] = vel(x, i);

        for (int j = 0; j < n; j++) {
            if (j != i) {
                rj = pos(x, j);
                x_dot[vel_sel(i)] += G * m[j] * (rj - ri)
                                     / pow(dist(rj, ri), 3);
            }
        }
    }
    
    return x_dot;
}

std::valarray<double> rk4_step(std::valarray<double> x, double m[], int n,
                          double dt) {
    std::valarray<double> k1(n * 6), k2(n * 6), k3(n * 6), k4(n * 6);

    k1 = dt * newton(x, m, n);
    k2 = dt * newton(x + k1 / 2.0, m, n);
    k3 = dt * newton(x + k2 / 2.0, m, n);
    k4 = dt * newton(x + k3, m, n);

    x += (k1 + 2.0 * k2 + 2.0 * k3 + k4) / 6.0;
    print_array(x);

    return x;
}

std::valarray<double> rk4_integrate(std::valarray<double> x, double m[],
                                    int n, double dt, int steps) {
    while (steps--) {
        x = rk4_step(x, m, n, dt);
    }

    return x;
}
