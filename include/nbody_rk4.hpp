#include <stdio.h>
#include <valarray>

class NBodyRK4: public NBody {
    private:
        std::valarray<double> ri;
        std::valarray<double> rj;
        std::valarray<double> k1;
        std::valarray<double> k2;
        std::valarray<double> k3;
        std::valarray<double> k4;

    public:
        NBodyRK4(int, int, double [], double, double, double [], bool, FILE *);
        std::valarray<double> newton_grav(std::valarray<double>);
        void step();
        void integrate(int);
};
