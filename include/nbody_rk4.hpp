/* An N-body integrator class using 4th-order Runge-Kutta (RK4) with adaptive
 * step sizes */

#ifndef NBODY_RK4_HPP
#define NBODY_RK4_HPP

#include <stdio.h>
#include <valarray>

class NBodyRK4: public NBody {
    private:
        // Various intermediate data arrays made to be class members for
        // convenience and code brevity
        std::valarray<double> ri;
        std::valarray<double> rj;
        std::valarray<double> k1;
        std::valarray<double> k2;
        std::valarray<double> k3;
        std::valarray<double> k4;
        std::valarray<double> X_new_1a;
        std::valarray<double> X_new_1b;
        std::valarray<double> X_new_2;
        
    public:
        NBodyRK4(int, int, double [], double [], bool, FILE *);
        std::valarray<double> newton_grav(std::valarray<double>);
        std::valarray<double> step(double, std::valarray<double>);
        double step_err(std::valarray<double>, std::valarray<double>);
        void integrate(double, double, double);
};

#endif // NBODY_RK4_HPP
