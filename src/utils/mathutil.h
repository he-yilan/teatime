#ifndef TEATIME_MATHUTIL_H
#define TEATIME_MATHUTIL_H

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

vec3c sub(vec3c &a, vec3c &b);
vec3c mul(mat3c &a, vec3c &b);

mat3c identity();
mat3c transpose(mat3c &m);
mat3c mul(mat3c &a, mat3c &b);
mat3c rotX(float deg);
mat3c rotY(float deg);
mat3c rotZ(float deg);
inline float dot(vec3c a, vec3c b);

template<typename T>
inline T radians(T deg) {
  return deg * (PI / 180);
}

template<typename T>
inline T degrees(T rad) {
  return rad * (180 / PI);
}

template<typename T>
inline T clamp(T v, T min, T max) {
  if (v >= min && v <= max) {
    return v;
  } else if (v < min) {
    return min;
  } else if (v > max) {
    return max;
  }
}

void readFile(const char *filepath, char *&out, long *fileSize);

#endif //TEATIME_MATHUTIL_H
