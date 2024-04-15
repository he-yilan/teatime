#include "sph.h"

using namespace std;

void SPH::Update(Fluid *f) {

  //Build ANN

  //Update density, pressure
  for (int i = 0; i < num_particles; i++) {
    Particle *p = f->particles.at(i);
    vector<Particle *> neighbors = f->particles; //TODO: Currently setting all particles as neighbors
    p->density = Density(p, &neighbors);
    p->pressure = Pressure(f, p->density);
  }

  //Update acceleration
  for (int i = 0; i < num_particles; ++i) {
    Particle *p = f->particles.at(i);
    vector<Particle *> *neighbors;
    // Get neighbors for Particle P (KD-tree, todo: import (ANN?) library)
    // Calculate density using neighbors (todo: why do we need to calculate this? we can just grab the particle's density, right?)
    Vector3D acceleration = Acceleration(f, neighbors, p);
    //p.forces = acceleration * p.mass; //  F = ma
    p->position += (acceleration * delta_t * delta_t); //todo: consider adding (pm->position - pm->last_position) to Verlet Integration for more exaggerated movements
    // Move P using acceleration and delta_t (todo: should we only modify forces and leave position to a higher-level process?
    // delta_v = acceleration on particle p due to pressure + viscosity + gravity + external forces
  }
}

double SPH::Density(Particle *p, vector<Particle *> *neighbors) {
  GaussianKernel gk;

  double total = 0;
  for (Particle *nbr : *neighbors) {
    double r = (p->position - nbr->position).norm();
    total += nbr->mass * gk.w(r);
  }
  return total;
}

double SPH::Pressure(Fluid *f, double density) {
  return c_s * c_s * (density - f->density);
}

Vector3D SPH::Acceleration(Fluid *f, vector<Particle *> *neighbors, Particle * p) {
  GaussianKernel gk;

  Vector3D a_pressure(0);
  for (Particle *nbr : *neighbors) {
    Vector3D P_ij = (-nbr->mass/nbr->density) * ((p->pressure/p->density*p->density) + (nbr->pressure/nbr->density*nbr->density));
    double r = (p->position - nbr->position).norm();
    a_pressure += P_ij * gk.w_first_derivative(r);
  }

  Vector3D a_viscosity(0);
  for (Particle *nbr : *neighbors) {
    Vector3D v_ij = -f->viscosity * (nbr->mass/nbr->density) * ((p->velocity/p->density*p->density) + (nbr->velocity/nbr->density*nbr->density));
    double r = (p->position - nbr->position).norm();
    a_viscosity += v_ij * gk.w_first_derivative(r);
  }

  Vector3D a_external = p->forces / p->density;

  Vector3D a_gravity = Vector3D(0, -g, 0);

  return a_pressure + a_viscosity + a_external + a_gravity;
}

double GaussianKernel::w(double r) {
  return (1 / (pow(M_PI, 1.5)*pow(h, 3))) * exp((r*r)/(h*h));
}

double GaussianKernel::w_first_derivative(double r) {
  //todo: add correct derivative expression
  return (1 / (pow(M_PI, 1.5)*pow(h, 3))) * (2*r / h*h) * exp((r*r)/(h*h));
}
