#ifndef SPHERE_H
#define SPHERE_H

#include "Shape.h"
#include "BRDF.h"

//****************************************************
// Sphere Header Definition
//****************************************************

class Sphere : public Shape {
  private:
    Coordinate* center;
    float radius;
  public:
    Sphere(Coordinate* cent, float rad);

    LocalGeo* intersect(Ray* ray);
    Vector* getNormal(Coordinate* pos);

};

#endif
