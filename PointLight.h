#ifndef POINTLIGHT_H
#define POINTLIGHT_H

//****************************************************
// PointLight Header Definition
//****************************************************

#include "Coordinate.h"
#include "Color.h"
#include "Ray.h"
#include "Vector.h"
#include "LocalGeo.h"

class PointLight : public Light {
  private:
    Coordinate* point;
    Color* color;

  public:
    PointLight(Coordinate* pos, Color* col);
    Ray* generateLightRay(LocalGeo* loc);
    Color* getColor() { return color; };
    bool isPointLight() { return true; };
    Vector* getLightDirection(Coordinate* pt);
};

#endif
