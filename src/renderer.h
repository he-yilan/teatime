#pragma once
#ifndef TEATIME_RENDERER_H
#define TEATIME_RENDERER_H

#ifndef GLAD_GL_IMPLEMENTATION
  #include <glad/gl.h>
#endif

#include <memory>
#include <vector>

#include "triangle.h"


class Renderer {
public:
    Renderer(std::vector<Triangle> &triangles);
    void render();
    bool isAlive();

private:
    bool alive = true;
    unsigned int VAO;
    unsigned int VBO;
    GLsizei n;
};


#endif //TEATIME_RENDERER_H
