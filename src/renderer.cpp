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

//  float arrayBuffer[] = {
//          // positions         // colors
//          0.5f, -0.5f, -1.0f,  1.0f, 0.0f, 0.0f, // bottom right
//          -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f, // bottom left
//          0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f,  // top
//          0.15f, -0.15f, 0.0f,  0.95f, 0.0f, 0.0f, // bottom right
//          -0.15f, -0.15f, 0.0f,  0.0f, 1.0f, 0.0f, // bottom left
//          -1.0f,  0.75f, 0.10f,  0.0f, 0.0f, 1.0f,  // top
//  };
//  Triangle points = {
//          // positions         // colors
//          0.5f, -0.5f, -2.0f,  // bottom right
//          -0.5f, -0.5f, 0.0f,  // bottom left
//          0.0f,  0.5f, 0.0f   // top
//
//  };
//  n = 3;
//  arrayBuffer = (Triangle*) calloc(1, sizeof(Triangle));
//  *arrayBuffer = points;

  glEnable(GL_DEPTH_TEST);

  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  glBindVertexArray(VAO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, n * sizeof(Triangle), arrayBuffer, GL_DYNAMIC_DRAW);

  GLint shaderProgram;
  glGetIntegerv(GL_CURRENT_PROGRAM, &shaderProgram);

  GLint posIdx = glGetAttribLocation(shaderProgram, "in_position");
  glVertexAttribPointer(posIdx, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*) nullptr);
  glEnableVertexAttribArray(posIdx);

//  GLint normalIdx = glGetAttribLocation(shaderProgram, "in_normal");
//  glVertexAttribPointer(normalIdx, 3, GL_FLOAT, GL_TRUE, stride, (void*)(9 * sizeof(float)));
//  glEnableVertexAttribArray(normalIdx);
//
//  GLint colorIdx = glGetAttribLocation(shaderProgram, "in_color");
//  glVertexAttribPointer(colorIdx, 3, GL_FLOAT, GL_FALSE, stride, (void*)(4 * sizeof(float)));
//  glEnableVertexAttribArray(colorIdx);

  GLint rotIdx = glGetUniformLocation(shaderProgram, "u_view_projection");
  mat3c *rot = (mat3c*)calloc(1, sizeof(mat3c));
  mat3c rx = rotY(45);
  mat3c rz = rotZ(45);
  *rot = mul(rx, rz);
//  *rot = rotZ(90);
//  *rot = identity();
  glUniformMatrix3fv(rotIdx, 1, GL_FALSE, (GLfloat*) rot);

//  free(arrayBuffer);
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
//  mat3c rotation;
//  mat3c rx = rotY(1);
//  mat3c rz = rotZ(1);
//  rotation = mul(rx, rz);
//  for (int i = 0; i < n; i++) {
//    *(&arrayBuffer->points + i) = mul(*(&arrayBuffer->points + i), rotation);
//  }
//  glBufferData(GL_ARRAY_BUFFER, n * sizeof(Triangle), arrayBuffer, GL_DYNAMIC_DRAW);

  glBindVertexArray(VAO);
  glDrawArrays(GL_TRIANGLES, 0, n);
}

bool Renderer::isAlive() {
  return alive;
}

void Renderer::renderParticles() {
  int timesteps = 10; // TODO: how many timesteps do we need
  double radius = 1.0; // TODO: what should radius be?
  BBox b; // TODO
  Fluid f(b, 997, 10); // density of water =  997 kg/m³ ?
  SPH s;
  for (int i = 0; i < timesteps; ++i) {
    // clear?
    // draw particles to screen using sphere rendering function
    for (Particle *p : f.particles) {
      // draw a sphere for every particle
      sphereMesh.draw_sphere(GL_FRAGMENT_SHADER, p->position, radius * 0.92);
    }
    // update positions
    s.Update(&f);
  }
}