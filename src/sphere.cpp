//
// Created by Austin George on 4/14/24.
//
#include "sphere.h"
#include "particle.h"

using namespace std;

// sphere.cpp from hw4
void Sphere::collide(Particle &p) {
  // (Part 3): Handle collisions with spheres.
  Vector3D d = pm.position - origin;
  if (d.norm() <= radius) {
    Vector3D tangent_point = origin + (d.unit() * radius);
    Vector3D correction = tangent_point - pm.last_position;
    pm.position = pm.last_position + ((1 - friction) * correction);
  }
}

/*
// sphere.cpp from hw4
void Sphere::render(GLShader &shader) {
  // We decrease the radius here so flat triangles don't behave strangely
  // and intersect with the sphere when rendered
  m_sphere_mesh.draw_sphere(shader, origin, radius * 0.92);
}
  */
