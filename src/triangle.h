#ifndef TEATIME_TRIANGLE_H
#define TEATIME_TRIANGLE_H

#include "utils/vector3D.h"

typedef struct vec3c {
    float x;
    float y;
    float z;
} vec3c;

typedef struct {
    vec3c p0;
    vec3c c0;
    vec3c p1;
    vec3c c1;
    vec3c p2;
    vec3c c2;
    vec3c n;
} Triangle;

#endif //TEATIME_TRIANGLE_H
