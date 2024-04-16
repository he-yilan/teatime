#include "renderer.h"
#include "fluid.h"
#include "sph.h"

Renderer::Renderer(std::vector<Triangle> &triangles) {
  int stride = 6 * sizeof(float);
  n = triangles.size();
  float *arrayBuffer = (float*)(calloc(n * sizeof(Triangle), sizeof(float)));
  for (int i = 0; i < triangles.size(); i++) {
    memcpy(arrayBuffer + (i * sizeof(Triangle) / sizeof(float)), &triangles.at(i), sizeof(Triangle));
  }

//  float arrayBuffer[] = {
//          // positions         // colors
//          0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom right
//          -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom left
//          0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f,  // top
//          0.15f, -0.15f, 0.0f,  0.95f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom right
//          -0.15f, -0.15f, 0.0f,  0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom left
//          -1.0f,  0.75f, 0.10f,  0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f,  // top
//  };
//  n = 6;

  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  glBindVertexArray(VAO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, n * stride, arrayBuffer, GL_DYNAMIC_DRAW);

  GLint shaderProgram;
  glGetIntegerv(GL_CURRENT_PROGRAM, &shaderProgram);

  GLint posIdx = glGetAttribLocation(shaderProgram, "in_position");
  glVertexAttribPointer(posIdx, 3, GL_FLOAT, GL_FALSE, stride, (void*) nullptr);
  glEnableVertexAttribArray(posIdx);

  GLint colorIdx = glGetAttribLocation(shaderProgram, "in_color");
  glVertexAttribPointer(colorIdx, 3, GL_FLOAT, GL_FALSE, stride, (void*)(3 * sizeof(float)));
  glEnableVertexAttribArray(colorIdx);

  GLint normalIdx = glGetAttribLocation(shaderProgram, "in_normal");
  glVertexAttribPointer(normalIdx, 3, GL_FLOAT, GL_TRUE, stride, (void*)(6 * sizeof(float)));
  glEnableVertexAttribArray(normalIdx);

//  glUniformMatrix4fv(glGetUniformLocation, 1, GL_FALSE, );

//  free(arrayBuffer);
}

void Renderer::render() {
  glEnable(GL_DEPTH_TEST);
  glBindVertexArray(VAO);
  glDrawArrays(GL_TRIANGLES, 0, n);
}

bool Renderer::isAlive() {
  return alive;
}

void Renderer::renderParticles() {
  int timesteps = 10;
  BBox b; // TODO
  Fluid f(b, 997, 10); // density of water =  997 kg/m³ ?
  SPH s;
  for (int i = 0; i < timesteps; ++i) {
    // draw particles to screen using sphere rendering function
    for (Particle *p : f.particles) {
      sphereMesh.draw_sphere(shader, p->position, 1.0); // radius = 1.0
    }
    // update positions
    s.Update(&f);
  }
}