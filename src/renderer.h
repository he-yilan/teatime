#pragma once
#ifndef TEATIME_RENDERER_H
#define TEATIME_RENDERER_H

#ifndef GLAD_GL_IMPLEMENTATION
  #include <glad/gl.h>
#endif

#include <memory>

class Renderer {
public:
    Renderer();
    void render();
    bool isAlive();

private:
    bool alive = true;
    unsigned int VAO;
    unsigned int VBO;
};


#endif //TEATIME_RENDERER_H
