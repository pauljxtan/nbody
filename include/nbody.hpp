/* The base n-body integrator class. */

#ifndef NBODY_HPP
#define NBODY_HPP

#include <stdio.h>
#include <valarray>

// Gravitational constant
static const double G = 1.0;

class NBody {
    protected:
        // Number of bodies in system
        int n_bodies;
        // Number of spatial dimensions
        int n_dims;
        // Masses
        double *m;
        // Elapsed time
        double t;
        // Current time step
        double dt;
        // Current system state (positions and velocities)
        std::valarray<double> X;
        // Stores solutions to ODEs
        std::valarray<double> X_dot;
        // Write flag
        bool write;
        // Output file pointer
        FILE *p_outfile;

    public:
        // Prints the current system state
        void print_state();
        // Writes the current system state to file
        void write_state();
        // Returns the distance between two vectors
        double dist(std::valarray<double>, std::valarray<double>);
        // Returns the position slice selector for the given body
        std::slice pos_sel(int);
        // Returns the velocity slice selector for the given body
        std::slice vel_sel(int);
        // Returns the position slice for the given body
        std::valarray<double> pos(std::valarray<double>, int);
        // Returns the velocity slice for the given body
        std::valarray<double> vel(std::valarray<double>, int);
};

#endif // NBODY_HPP
