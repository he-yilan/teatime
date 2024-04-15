#ifndef TEATIME_PARTICLE_H
#define TEATIME_PARTICLE_H

#include "utils/vector3D.h"
#include "utils/bbox.h"
#include "fluid.h"

class Particle {
public:
    Particle(Vector3D position);
    void update(int timestep);

    Vector3D position;
    Vector3D velocity;
    float mass;
    Vector3D color;
    Vector3D forces;
    double pressure;
    double density;


private:
    //todo: add things? maybe??
};

#endif //TEATIME_PARTICLE_H