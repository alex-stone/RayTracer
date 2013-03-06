#ifndef SHAPE_H
#define SHAPE_H

#include "LocalGeo.h"
#include "Ray.h"
#include "Vector.h"
#include "Coordinate.h"

//****************************************************
// Shape Header Definition
//****************************************************

class Shape {
  public:
    virtual LocalGeo* intersect(Ray* ray) = 0;
    virtual bool intersectP(Ray* ray) = 0;
    virtual Vector* getNormal(Coordinate* pos) = 0;

};

#endif
