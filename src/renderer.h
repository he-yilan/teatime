#pragma once
#ifndef TEATIME_RENDERER_H
#define TEATIME_RENDERER_H

#ifndef GLAD_GL_IMPLEMENTATION
  #include <glad/gl.h>
#endif

#include <memory>
#include <vector>

#include "triangle.h"

class SphereMesh;

class Renderer {
public:
    Renderer(std::vector<Triangle> &triangles);
    void render();
    void renderParticles();

private:
    unsigned int VAO;
    unsigned int VBO;
    GLsizei n;
    Triangle *arrayBuffer;
    float r = 0;
    vec3c *lightPos;
};


#endif //TEATIME_RENDERER_H
