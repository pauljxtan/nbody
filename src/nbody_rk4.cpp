#include <cmath>
#include <cstdlib>
#include <iostream>
#include <valarray>
#include "nbody.hpp"
#include "nbody_rk4.hpp"

// TODO:
//     adaptive step sizes

NBodyRK4::NBodyRK4(int n_bodies, int n_dims, double m[], double dt_init,
                   double t_init, double X_init[], bool write,
                   FILE *p_outfile) {
    this->n_bodies = n_bodies;
    this->n_dims = n_dims;
    this->m = (double *) malloc(n_bodies * sizeof(double));
    for (int i = 0; i < n_bodies; i++)
        this->m[i] = m[i];
    this->dt = dt_init;
    this->t = t_init;
    this->X.resize(2 * n_dims * n_bodies);
    for (int i = 0; i < 2 * n_dims * n_bodies; i++)
        this->X[i] = X_init[i];
    this->write = write;
    this->p_outfile = p_outfile;

    this->ri.resize(n_dims);
    this->rj.resize(n_dims);
    this->k1.resize(2 * n_dims * n_bodies);
    this->k2.resize(2 * n_dims * n_bodies);
    this->k3.resize(2 * n_dims * n_bodies);
    this->k4.resize(2 * n_dims * n_bodies);
    this->x_dot.resize(2 * n_dims * n_bodies, 0.0);

    print_state();
}
std::valarray<double> NBodyRK4::newton_grav(std::valarray<double> x) {
    //std::valarray<double> x_dot(0.0, 2 * n_dims * n_bodies);
    // set all values to zero
    x_dot -= x_dot;

    for (int i = 0; i < n_bodies; i++) {
        ri = pos(x, i);
        x_dot[pos_sel(i)] = vel(x, i);

        for (int j = 0; j < n_bodies; j++) {
            if (j != i) {
                rj = pos(x, j);
                x_dot[vel_sel(i)] += G * m[j] * (rj - ri)
                                     / pow(dist(rj, ri), 3);
            }
        }
    }
    return x_dot;
}

void NBodyRK4::step() {
    k1 = dt * newton_grav(X);
    k2 = dt * newton_grav(X + k1 / 2.0);
    k3 = dt * newton_grav(X + k2 / 2.0);
    k4 = dt * newton_grav(X + k3);
    
    t += dt;
    X += (k1 + 2.0 * k2 + 2.0 * k3 + k4) / 6.0;

    print_state();
    if (write)
        write_state();
}

void NBodyRK4::integrate(int n_steps) {
    while (n_steps--)
        step();
}