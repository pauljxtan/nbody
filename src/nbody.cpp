#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <valarray>
#include "nbody.hpp"

void NBody::print_state() {
    std::cout << t << " ";
    for (unsigned i = 0; i < X.size() - 1; i++)
        std::cout << X[i] << " ";
    std::cout << X[X.size() - 1] << "\n";
}

void NBody::write_state() {
    std::fprintf(p_outfile, "%f ", t);
    for (unsigned i = 0; i < X.size() - 1; i++)
        std::fprintf(p_outfile, "%f ", X[i]);
    fprintf(p_outfile, "%f\n", X[X.size() - 1]);
}

double NBody::dist(std::valarray<double> a, std::valarray<double> b) {
    return std::sqrt(std::pow(b - a, 2).sum());
}

std::slice NBody::pos_sel(int i_body) {
    return std::slice(2 * n_dims * i_body, n_dims, 1);
}

std::slice NBody::vel_sel(int i_body) {
    return std::slice(2 * n_dims * i_body + n_dims, n_dims, 1);
}

std::valarray<double> NBody::pos(std::valarray<double> x, int i_body) {
    return x[pos_sel(i_body)];
}

std::valarray<double> NBody::vel(std::valarray<double> x, int i_body) {
    return x[vel_sel(i_body)];
}
