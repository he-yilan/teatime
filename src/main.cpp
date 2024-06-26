#define GLAD_GL_IMPLEMENTATION
#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include <cstdio>
#include <iostream>

#include "renderer.h"
#include "utils/mathutil.h"

GLFWwindow *window = nullptr;
Renderer *renderer = nullptr;

void error_callback(int error, const char* description) {
  puts(description);
}

void createGLContexts() {
  if (!glfwInit()) {
    return;
  }

  glfwSetTime(0);

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  glfwWindowHint(GLFW_SAMPLES, 0);
  glfwWindowHint(GLFW_RED_BITS, 8);
  glfwWindowHint(GLFW_GREEN_BITS, 8);
  glfwWindowHint(GLFW_BLUE_BITS, 8);
  glfwWindowHint(GLFW_ALPHA_BITS, 8);
  glfwWindowHint(GLFW_STENCIL_BITS, 8);
  glfwWindowHint(GLFW_DEPTH_BITS, 24);
  glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

  window = glfwCreateWindow(800, 800, "teatime", nullptr, nullptr);
  if (window == nullptr) {
    std::cout << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    return;
  }
  glfwMakeContextCurrent(window);
  if (!gladLoadGL(glfwGetProcAddress)) {
    glfwTerminate();
    return;
  }

  glClearColor(0.2f, 0.25f, 0.3f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);

  int width;
  int height;
  glfwGetFramebufferSize(window, &width, &height);
  glViewport(0, 0, width, height);
  glfwSwapInterval(1);
  glfwSwapBuffers(window);
}

unsigned int loadShaderFromFile(const char *filepath, GLenum type) {
  unsigned int shaderHandle = glCreateShader(type);
  char *shaderSource = nullptr;
  readFile(filepath, shaderSource, nullptr);
  glShaderSource(shaderHandle, 1, &shaderSource, nullptr);
  glCompileShader(shaderHandle);
  int success;
  glGetShaderiv(shaderHandle, GL_COMPILE_STATUS, &success);
  if (!success) {
    char infoLog[512];
    glGetShaderInfoLog(shaderHandle, 512, nullptr, infoLog);
    std::cerr << "ERROR: Shader compilation failed:\n" << infoLog << std::endl;
  }
  free(shaderSource);
  return shaderHandle;
}

void createShaders() {
  unsigned int vertexShader = loadShaderFromFile("../shaders/Default.vert", GL_VERTEX_SHADER);
  unsigned int fragmentShader = loadShaderFromFile("../shaders/Diffuse.frag", GL_FRAGMENT_SHADER);

  GLint shaderProgram = glCreateProgram();
  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);
  glLinkProgram(shaderProgram);

  int success;
  glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
  if (!success) {
    char infoLog[512];
    glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
    std::cout << "ERROR: Shader linking failed: \n" << infoLog << std::endl;
  }
  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);

  glUseProgram(shaderProgram);
}

void cursorCallback(GLFWwindow *w, double x, double y) {
}

void mouseButtonCallback(GLFWwindow *w, int button, int action, int modifiers) {
}

void keyCallback(GLFWwindow *w, int key, int scancode, int action, int mods) {
  switch (key) {
    case GLFW_KEY_C:
      if (mods & GLFW_MOD_CONTROL) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
      }
  }
}

void charCallback(GLFWwindow *w, unsigned int codepoint) {
}

void scrollCallback(GLFWwindow *w, double x, double y) {
}

void framebufferSizeCallback(GLFWwindow *w, int width, int height) {
}

void setGLFWCallbacks() {
  glfwSetCursorPosCallback(window, cursorCallback);
  glfwSetMouseButtonCallback(window, mouseButtonCallback);
  glfwSetKeyCallback(window, keyCallback);
  glfwSetCharCallback(window, charCallback);
  glfwSetScrollCallback(window, scrollCallback);
  glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
}

void loadBinarySTL(const char *filepath, std::vector<Triangle> &out) {
  char *fileBytes = nullptr;
  long fileSize = -1;
  readFile(filepath, fileBytes, &fileSize);

  int stride = 3 * sizeof(float);
  for (int i = 84; i < fileSize; i += 50) {
    Triangle t;
    memcpy(&t.n0, &fileBytes[i], stride);
    t.n2 = t.n1 = t.n0;
    memcpy(&t.p0, &fileBytes[i + stride], stride);
    memcpy(&t.p1, &fileBytes[i + (2 * stride)], stride);
    memcpy(&t.p2, &fileBytes[i + (3 * stride)], stride);
    out.emplace_back(t);
  }
}

int main(int argc, char **argv) {
  srand(5818);
  glfwSetErrorCallback(error_callback);

  createGLContexts();
  setGLFWCallbacks();
  createShaders();

  std::vector<Triangle> triangles = std::vector<Triangle>();
  loadBinarySTL("../models/glass_teacup_smaller.stl", triangles);
  renderer = new Renderer(triangles);

  while (!glfwWindowShouldClose(window)) {
    glfwPollEvents();

    glClearColor(0.25f, 0.25f, 0.25f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    renderer->render();

    glfwSwapBuffers(window);
  }

  glfwTerminate();
  return 0;
}