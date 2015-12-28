#ifndef NBODY_HPP
#define NBODY_HPP

#include <stdio.h>
#include <valarray>

/*! @file */

static const double G = 1.0; //!< Gravitational constant

//! The base (abstract) N-body integrator class.
class NBody {
    protected:
        int n_bodies; //!< Number of bodies in system
        int n_dims; //!< Number of spatial dimensions
        double * m; //!< Masses
        double t; //!< Elapsed time
        double dt; //!< Current time step
        std::valarray<double> X; //!< Current system state (positions and velocities)
        std::valarray<double> X_dot; //!< Stores solutions to ODEs
        bool write; //!< Write flag
        FILE * p_outfile; //!< Output file pointer

        //! Prints the current system state
        void print_state();
        //! Writes the current system state to file
        void write_state();
        //! Returns the distance between two vectors
        double dist(std::valarray<double>, std::valarray<double>);
        //! Returns the position slice selector for the given body
        std::slice pos_sel(int);
        //! Returns the velocity slice selector for the given body
        std::slice vel_sel(int);
        //! Returns the position slice for the given body
        std::valarray<double> pos(std::valarray<double>, int);
        //! Returns the velocity slice for the given body
        std::valarray<double> vel(std::valarray<double>, int);

        virtual std::valarray<double> step(double, std::valarray<double>) = 0;
};

#endif // NBODY_HPP
