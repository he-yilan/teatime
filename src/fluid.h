
#ifndef TEATIME_FLUID_H
#define TEATIME_FLUID_H

#include "particle.h"

using namespace std;

class Fluid {
public:
    Fluid(BBox bb, float density, int n);
    vector<Particle> particles;
    void InitParticles(int n, BBox bb);
//    void simulate(double frames_per_sec, double simulation_steps, Fluid *f,
//                  vector<Vector3D> external_accelerations);

    float viscosity;
    float density;
    float mass;
private:
    //
};


#endif //TEATIME_FLUID_H
