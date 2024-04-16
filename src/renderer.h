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
    bool isAlive();
    void renderParticles();

private:
    bool alive = true;
    unsigned int VAO;
    unsigned int VBO;
    GLsizei n;
<<<<<<< HEAD
    GLFW::Misc::SphereMesh sphereMesh;
=======
>>>>>>> 8c5cd8ab1b3cd0e23fa77eaec880cf7cfa48268d
    Triangle *arrayBuffer;
    float r = 0;
};


#endif //TEATIME_RENDERER_H
