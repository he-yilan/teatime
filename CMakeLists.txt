cmake_minimum_required(VERSION 2.8)
project(teatime)

set(CMAKE_CXX_STANDARD 11)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(glfw/)

find_package(OpenGL REQUIRED)
add_executable(teatime main.cpp)

target_link_libraries(teatime glfw)
target_link_libraries(teatime OpenGL::GL)
