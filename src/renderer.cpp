#include "renderer.h"
#include "fluid.h"
#include "sph.h"

Renderer::Renderer(std::vector<Triangle> &triangles) {
  r = 0;
  n = triangles.size();
  arrayBuffer = (Triangle*)(calloc(n, sizeof(Triangle)));
  for (int i = 0; i < triangles.size(); i++) {
    memcpy(arrayBuffer + i, &triangles.at(i), sizeof(Triangle));
  }

  glEnable(GL_DEPTH_TEST);

  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  glBindVertexArray(VAO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, n * sizeof(Triangle), arrayBuffer, GL_DYNAMIC_DRAW);

  GLint shaderProgram;
  glGetIntegerv(GL_CURRENT_PROGRAM, &shaderProgram);

  GLint posIdx = glGetAttribLocation(shaderProgram, "in_position");
  glVertexAttribPointer(posIdx, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*) nullptr);
  glEnableVertexAttribArray(posIdx);

  GLint normalIdx = glGetAttribLocation(shaderProgram, "in_normal");
  glVertexAttribPointer(normalIdx, 3, GL_FLOAT, GL_TRUE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
  glEnableVertexAttribArray(normalIdx);
}

void Renderer::render() {
  GLint shaderProgram;
  glGetIntegerv(GL_CURRENT_PROGRAM, &shaderProgram);
  GLint rotIdx = glGetUniformLocation(shaderProgram, "u_view_projection");
  mat3c *rot = (mat3c*)calloc(1, sizeof(mat3c));
  mat3c rx = rotY(r);
  mat3c rz = rotZ(r);
  *rot = mul(rx, rz);
  r++;
//  *rot = rotZ(r++);
//  *rot = identity();
  glUniformMatrix3fv(rotIdx, 1, GL_FALSE, (GLfloat*) rot);

  glBindVertexArray(VAO);
  glDrawArrays(GL_TRIANGLES, 0, n * 3);
}

bool Renderer::isAlive() {
  return alive;
}

//void Renderer::renderParticles() {
//  int timesteps = 10;
//  BBox b; // TODO
//  Fluid f(b, 997, 10); // density of water =  997 kg/m³ ?
//  SPH s;
//  for (int i = 0; i < timesteps; ++i) {
//    // draw particles to screen using sphere rendering function
//    for (Particle *p : f.particles) {
//      sphereMesh.draw_sphere(shader, p->position, 1.0); // radius = 1.0
//    }
//    // update positions
//    s.Update(&f);
//  }
//}