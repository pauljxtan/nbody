# nbody #

N-body simulations in C++.

### Integrators ###

* __NBodyRK4__: Integrates a system of N gravitationally interacting bodies
                using the 4th-order Runge-Kutta method, with adaptive step
                sizes.
                This is a direct, particle-particle integration with O(N^2)
                complexity -- prohibitively slow for large N.
                (Stay tuned for faster integrators.)

### Quick start ###

* Input parameter file: params
* Output data file: results
```bash
$ ./src/integrate -p params -w results
```
(Note: standard output is switched off if writing to file)

### Input parameter file ###

* First row: Number of bodies, number of dimensions, integration duration,
             initial time step, desired accuracy
* Each remaining row: Mass of body, initial position in each dimension,
                      initial speed in each dimension

### Real-time plotting ###

An example Python script (requires matplotlib) __plot_realtime_N3.py__ is included for viewing the orbits in real time. One could pipe the integration data directly from the simulator like so:
```bash
$ ./src/integrate -p params | ./plot_realtime.py [frameskip]
```
or read it in from a results file:
```bash
$ ./plot_realtime.py < results
```
N.B. This script includes a plethora of hard-coded parameters (for N=3), and may have to be modified to suit your particular system.

### To-do ###

* Faster methods (tree code, multipole, mean field, etc.)
* Generalized interaction function
