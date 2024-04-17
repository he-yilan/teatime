#include "mathutil.h"

void readFile(const char *filepath, char *&out, long *fileSize) {
  FILE *fp = fopen( filepath, "rb");
  fseek(fp, 0L, SEEK_END);
  long size = ftell(fp);
  if (fileSize != nullptr) {
    *fileSize = size;
  }
  rewind(fp);

  out = static_cast<char *>(calloc(1, size + 1));
  fread(out, size, 1, fp);
  fclose(fp);
}

vec3c sub(vec3c &a, vec3c &b) {
  return {
          a.x - b.x,
          a.y - b.y,
          a.z - b.z
  };
}

vec3c mul(mat3c &a, vec3c &b) {
  return {
    dot(a.row0, b),
    dot(a.row1, b),
    dot(a.row2, b)
  };
}

mat3c transpose(mat3c m) {
  return {
    m.row0.x, m.row1.x, m.row2.x,
    m.row0.y, m.row1.y, m.row2.y,
    m.row0.z, m.row1.z, m.row2.z,
  };
}

mat3c identity() {
  return {
          1, 0, 0,
          0, 1, 0,
          0, 0, 1
  };
}

mat3c mul(mat3c &a, mat3c &b) {
  return {
          (a.row0.x * b.row0.x) + (a.row0.y * b.row1.x) + (a.row0.z * b.row2.x),
          (a.row0.x * b.row0.y) + (a.row0.y * b.row1.y) + (a.row0.z * b.row2.y),
          (a.row0.x * b.row0.z) + (a.row0.y * b.row1.z) + (a.row0.z * b.row2.z),

          (a.row1.x * b.row0.x) + (a.row1.y * b.row1.x) + (a.row1.z * b.row2.x),
          (a.row1.x * b.row0.y) + (a.row1.y * b.row1.y) + (a.row1.z * b.row2.y),
          (a.row1.x * b.row0.z) + (a.row1.y * b.row1.z) + (a.row1.z * b.row2.z),

          (a.row2.x * b.row0.x) + (a.row2.y * b.row1.x) + (a.row2.z * b.row2.x),
          (a.row2.x * b.row0.y) + (a.row2.y * b.row1.y) + (a.row2.z * b.row2.y),
          (a.row2.x * b.row0.z) + (a.row2.y * b.row1.z) + (a.row2.z * b.row2.z),
  };
}

mat3c rotX(float deg) {
  float rad = deg * PI / 180;
  float cosTheta = std::cos(rad);
  float sinTheta = std::sin(rad);
  return {
          1, 0, 0,
          0, cosTheta, -sinTheta,
          0, sinTheta, cosTheta
  };
}

mat3c rotY(float deg) {
  float rad = deg * PI / 180;
  float cosTheta = std::cos(rad);
  float sinTheta = std::sin(rad);
  return {
    cosTheta, 0, sinTheta,
    0, 1, 0,
    -sinTheta, 0, cosTheta
  };
}

mat3c rotZ(float deg) {
  float rad = deg * PI / 180;
  float cosTheta = std::cos(rad);
  float sinTheta = std::sin(rad);
  return {
    cosTheta, -sinTheta, 0,
    sinTheta, cosTheta, 0,
    0, 0, 1
  };
}

inline float dot(vec3c a, vec3c b) {
  return (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
}