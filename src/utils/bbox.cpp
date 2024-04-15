//Credit: CS184 Course Staff (HW3)

#include "bbox.h"

/** Returns a random position inside the bounding box */
Vector3D BBox::randomPosition() const {
  double randX = min.x + (rand() / (double)RAND_MAX) * extent.x;
  double randY = min.y + (rand() / (double)RAND_MAX) * extent.y;
  double randZ = min.z + (rand() / (double)RAND_MAX) * extent.z;
  return { randX, randY, randZ };
}
