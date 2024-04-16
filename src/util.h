#ifndef TEATIME_UTIL_H
#define TEATIME_UTIL_H

#define PI 3.141529

#include <cmath>
#include <cstdio>
#include <cstdlib>

typedef struct vec3c {
    float x;
    float y;
    float z;
} vec3c;

typedef struct mat3c {
    vec3c row0;
    vec3c row1;
    vec3c row2;
} mat3c;

mat3c identity();
mat3c transpose(mat3c m);
mat3c mul(mat3c &a, mat3c &b);
mat3c rotX(float deg);
mat3c rotY(float deg);
mat3c rotZ(float deg);
inline float dot(vec3c a, vec3c b);

void readFile(const char *filepath, char *&out, long *fileSize);

#endif //TEATIME_UTIL_H
