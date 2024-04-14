cmake_minimum_required(VERSION 3.6)
project(teatime)

set(CMAKE_CXX_STANDARD 11)

find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIRS})

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(glfw)

include_directories("${GLFW_SOURCE_DIR}/deps")
set(GLAD_GL "${GLFW_SOURCE_DIR}/deps/glad/gl.h")

if(MSVC)
    SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /ENTRY:mainCRTStartup")
endif()

include_guard(GLOBAL)
set(TEATIME_FILES
        src/renderer.cpp
        src/renderer.h
        src/util.cpp
        src/util.h
        src/main.cpp
)

add_executable(teatime WIN32 ${TEATIME_FILES} ${GLAD_GL})
target_link_libraries(teatime ${OPENGL_LIBRARIES} glfw)