#include <stdio.h>
#include <valarray>

static const double G = 1.0;

class NBody {
    protected:
        int n_bodies;
        int n_dims;
        double *m;
        double dt;
        double t;
        std::valarray<double> X;
        std::valarray<double> x_dot;
        bool write;
        FILE *p_outfile;

    public:
        void print_state();
        void write_state();
        double dist(std::valarray<double>, std::valarray<double>);
        std::slice pos_sel(int);
        std::slice vel_sel(int);
        std::valarray<double> pos(std::valarray<double>, int);
        std::valarray<double> vel(std::valarray<double>, int);
};
