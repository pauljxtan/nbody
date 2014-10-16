# nbody #

N-body simulations in C++.

### Integrators ###
* __NBodyRK4__: integrates a system of n gravitationally interacting bodies
                using the 4th-order Runge-Kutta method, with adaptive step
                sizes

### Quick start ###
* Input parameter file: params
* Output data file: results
```bash
$ ./src/integrate -p params -w results
```

### Input parameter file ###
* First row: Number of bodies, number of dimensions, integration duration,
             initial time step, desired accuracy
* Each remaining row: Mass of body, initial position in each dimension,
                      initial speed in each dimension
