//Credit: CS184 Course Staff (HW3)

#ifndef TEATIME_BBOX_H
#define TEATIME_BBOX_H

#include "vector3D.h"

class BBox {
public:
    Vector3D min;	    // min corner of the bounding box
    Vector3D max;	    // max corner of the bounding box
    Vector3D extent;  // max - min
    Vector3D randomPosition() const; // returns a random position in the bounding box
};


#endif //TEATIME_BBOX_H
