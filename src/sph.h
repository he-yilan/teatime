//
// Created by Austin George on 4/14/24.
//

#ifndef TEATIME_SPH_H
#define TEATIME_SPH_H

#include "fluid.h"
#include "math.h"
#include "stdlib.h"

struct SPH {
    //Params, todo: move to Simulator class
    double delta_t = 0.005;
    int num_particles = 100; // num particles
    double c_s = 1500;  // speed of sound

    void Update(Fluid *f);
    double Density(Particle* p, vector<Particle *> *neighbors);
    double Pressure(Fluid* f, double density);
    Vector3D Acceleration(Fluid *f, vector<Particle *> *neighbors, Particle *p);
    double g = 9.8;
};

struct GaussianKernel {
    //Smoothing width
    double h = 0.5;

    //r = Euclidean distance between two particles
    double w(double r);

    double w_first_derivative(double r);
};


#endif //TEATIME_SPH_H
