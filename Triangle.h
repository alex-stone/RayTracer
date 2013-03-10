#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "Shape.h"
#include "Coordinate.h"
#include "Vector.h"
#include "LocalGeo.h"
#include "Ray.h"

//****************************************************
// Triangle Header Definition
//****************************************************

class Triangle : public Shape {
  private:
    Coordinate* v1;
    Coordinate* v2;
    Coordinate* v3;
    Vector* normal;

  public:
    // Triangle Constructor
    Triangle(Coordinate* vec1, Coordinate* vec2, Coordinate* vec3);

    // Shape - Abstract functions
    LocalGeo* intersect(Ray* ray);
    bool intersectP(Ray* ray);
    Vector* getNormal(Coordinate* pos) { return normal; };

    bool isPointInTriangle(Coordinate* pos);
};

#endif
