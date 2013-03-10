#ifndef SPHERE_H
#define SPHERE_H

#include "Shape.h"
#include "Coordinate.h"
#include "Vector.h"
#include "Ray.h"

//****************************************************
// Sphere Header Definition
//****************************************************

class Sphere : public Shape {
  private:
    Coordinate* center;
    float radius;
  public:
    // Sphere Constructor
    Sphere(Coordinate* cent, float rad);

    // Shape - Abstract Functions
    LocalGeo* intersect(Ray* ray);
    bool intersectP(Ray* ray);
    Vector* getNormal(Coordinate* pos);

};

#endif
