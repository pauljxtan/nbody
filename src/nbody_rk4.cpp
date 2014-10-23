#include <cmath>
#include <cstdlib>
#include <iostream>
#include <valarray>
#include "nbody.hpp"
#include "nbody_rk4.hpp"

// TODO:
//     adaptive step sizes

NBodyRK4::NBodyRK4(int n_bodies, int n_dims, double m[], double X_init[],
                   bool write, FILE *p_outfile) {
    this->n_bodies = n_bodies;
    this->n_dims = n_dims;
    this->m = (double *) malloc(n_bodies * sizeof(double));
    for (int i = 0; i < n_bodies; i++) this->m[i] = m[i];
    this->t = 0.0;
    this->X.resize(2 * n_dims * n_bodies);
    for (int i = 0; i < 2 * n_dims * n_bodies; i++) this->X[i] = X_init[i];
    this->X_dot.resize(2 * n_dims * n_bodies, 0.0);
    this->X_new_1a.resize(2 * n_dims * n_bodies);
    this->X_new_1b.resize(2 * n_dims * n_bodies);
    this->X_new_2.resize(2 * n_dims * n_bodies);
    this->write = write;
    this->p_outfile = p_outfile;

    this->ri.resize(n_dims);
    this->rj.resize(n_dims);
    this->k1.resize(2 * n_dims * n_bodies);
    this->k2.resize(2 * n_dims * n_bodies);
    this->k3.resize(2 * n_dims * n_bodies);
    this->k4.resize(2 * n_dims * n_bodies);

    if (!write) print_state();
}
std::valarray<double> NBodyRK4::newton_grav(std::valarray<double> X) {
    // Reset all values to zero
    X_dot -= X_dot;

    for (int i = 0; i < n_bodies; i++) {
        ri = pos(X, i);
        X_dot[pos_sel(i)] = vel(X, i);

        for (int j = 0; j < n_bodies; j++) {
            if (j != i) {
                rj = pos(X, j);
                X_dot[vel_sel(i)] += G * m[j] * (rj - ri)
                                     / pow(dist(rj, ri), 3);
            }
        }
    }
    return X_dot;
}

std::valarray<double> NBodyRK4::step(double dt, std::valarray<double> X) {
    k1 = dt * newton_grav(X);
    k2 = dt * newton_grav(X + k1 / 2.0);
    k3 = dt * newton_grav(X + k2 / 2.0);
    k4 = dt * newton_grav(X + k3);
    
    return X + (k1 + 2.0 * k2 + 2.0 * k3 + k4) / 6.0;
}

double NBodyRK4::step_err(std::valarray<double> X1, std::valarray<double> X2) {
    eps_sum_sq = 0.0;

    for (int i = 0; i < n_bodies; i++) {
        for (int j = 0; j < n_dims; j++)
            // Get epsilons for position only (not velocity)
            eps_sum_sq += std::pow((pos(X1, i)[j] - pos(X2, i)[j]) / 30.0, 2);
    }

    return std::sqrt(eps_sum_sq);
}

void NBodyRK4::integrate(double dur, double dt_init, double delta) {
    double dt = dt_init;
    double t_start = t;

    while (t < t_start + dur) {
        // First estimate
        X_new_1a = step(dt, X);
        X_new_1b = step(dt, X_new_1a);
        // Second estimate
        X_new_2 = step(2.0 * dt, X);

        rho = delta * dt / step_err(X_new_1b, X_new_2);
        if (rho > 1.0) {
            // Keep step, adjust step size, move on to next iteration
            t += dt;
            X = X_new_1a;
            dt *= std::pow(rho, 0.25);
        }
        else {
            // Adjust step size, redo step, then move on to next iteration
            dt *= std::pow(rho, 0.25);
            t += dt;
            X = step(dt, X);
        }

        if (write) write_state();
        else       print_state();
    }
}
