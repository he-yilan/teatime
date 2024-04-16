#include "fluid.h"
#include "utils/bbox.h"
#include "particle.h"

using namespace std;

Fluid::Fluid(BBox bb, float density, int n) {
  InitParticles(n, bb);
  //Initialize mass
  double volume = bb.extent.x * bb.extent.y * bb.extent.z;
  mass = density * volume;
}


void Fluid::InitParticles(int n, BBox bb) {
  for (int i = 0; i < n; i++) {
    //Pick a random world-coordinate in the bounding box
    Vector3D position = bb.randomPosition();
    Particle particle = Particle(position);
    particle.mass = mass / (float)n;
    particle.velocity = 0; //todo: should particle start at rest?
    particle.density = density;
    particles.push_back(&particle);
  }
}

/*
// also need vector<CollisionObject *> *collision_objects as a parameter, will add later
void Fluid::simulate(double frames_per_sec, double simulation_steps, Fluid *f,
                     vector<Vector3D> external_accelerations) {
  // call SPH update
}

*/

//TODO: Update p.forces based on scene collisions (i.e. normal of teapot) & gravity before calling SPH