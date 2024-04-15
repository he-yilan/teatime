#include "particle.h"

using namespace std;

Particle::Particle(Vector3D position) {
  this->position = position;
  //todo: initialize the rest to appropriate default values
}

void Particle::update(int timestep) {
  // update velocity, density, pressure?
}
