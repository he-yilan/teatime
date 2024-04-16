#pragma once
#ifndef TEATIME_RENDERER_H
#define TEATIME_RENDERER_H

#ifndef GLAD_GL_IMPLEMENTATION
  #include <glad/gl.h>
#endif

#include <memory>
#include <vector>

#include "triangle.h"
#include "../sphere_drawing.h"

class SphereMesh;

class Renderer {
public:
    Renderer(std::vector<Triangle> &triangles);
    void render();
    bool isAlive();
    void renderParticles();

private:
    bool alive = true;
    unsigned int VAO;
    unsigned int VBO;
    GLsizei n;
    CGL::Misc::SphereMesh sphereMesh;
};


#endif //TEATIME_RENDERER_H
