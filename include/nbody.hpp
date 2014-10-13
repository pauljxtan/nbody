#ifndef NBODY_HPP
#define NBODY_HPP

#include <valarray>

static const double G = 1.0;

void print_array(std::valarray<double>);
double dist(std::valarray<double>, std::valarray<double>);
std::valarray<double> pos(std::valarray<double>, int);
std::valarray<double> vel(std::valarray<double>, int);
std::slice pos_sel(int);
std::slice vel_sel(int);
std::valarray<double> newton(std::valarray<double>, double [], int);
std::valarray<double> rk4_step(std::valarray<double>, double [], int, double);
std::valarray<double> rk4_integrate(std::valarray<double>, double [], int,
                                    double, int);

#endif // NBODY_HPP
