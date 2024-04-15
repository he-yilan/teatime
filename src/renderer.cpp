#include "renderer.h"

Renderer::Renderer(std::vector<Triangle> &triangles) {
  int n = triangles.size();
  float *arrayBuffer = static_cast<float *>(calloc(n * 6, sizeof(float)));
  int stride = 6 * sizeof(float);
  for (int i = 0; i < n; i++) {
    memcpy(arrayBuffer + (i * stride), &triangles.at(i), stride);
  }

  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  glBindVertexArray(VAO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(arrayBuffer), arrayBuffer, GL_DYNAMIC_DRAW);

  glVertexAttribPointer(0, n, GL_FLOAT, GL_FALSE, stride, (void*) nullptr);
  glEnableVertexAttribArray(0);

  glVertexAttribPointer(1, n, GL_FLOAT, GL_FALSE, stride, (void*)(n * sizeof(float)));
  glEnableVertexAttribArray(1);

  glBindVertexArray(VAO);
  free(arrayBuffer);
}

void Renderer::render() {
  glDrawArrays(GL_TRIANGLES, 0, 3);
}

bool Renderer::isAlive() {
  return alive;
}