#ifndef CGL_UTIL_SPHEREDRAWING_H
#define CGL_UTIL_SPHEREDRAWING_H

#include <vector>

#include "utils/mathutil.h"
#include "utils/vector3D.h"

class SphereMesh {
public:
    // Supply the desired number of vertices
    SphereMesh(int num_lat = 40, int num_lon = 40);

    /**
     * Draws a sphere with the given position and radius in opengl, using the
     * current modelview/projection matrices and color/material settings.
     */
    void draw_sphere(const Vector3D &p, double r);
private:
    std::vector<unsigned int> Indices;
    std::vector<double> Vertices;

    int s_index(int x, int y);

    void build_data();

    int sphere_num_lat;
    int sphere_num_lon;

    int sphere_num_vertices;
    int sphere_num_indices;

    MatrixXf positions;
    MatrixXf normals;
    MatrixXf uvs;
    MatrixXf tangents;
};

#endif // CGL_UTIL_SPHEREDRAWING_H
