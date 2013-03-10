#ifndef LIGHT_H
#define LIGHT_H

//****************************************************
// Light Header Definition
//****************************************************

#include "Ray.h"
#include "Color.h"
#include "Coordinate.h"
#include "LocalGeo.h"
#include "Vector.h"

class Light {

  public:
    virtual Ray* generateLightRay(LocalGeo* loc)=0;
    virtual Color* getColor() = 0;
    virtual bool isPointLight() = 0;
    virtual Vector* getLightDirection(Coordinate* pt) = 0;
};
#endif
