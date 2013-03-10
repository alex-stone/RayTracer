#include <iostream>
#include <math.h>

#include "Light.h"
#include "PointLight.h"
#include "Coordinate.h"
#include "Color.h"
#include "Vector.h"
#include "Ray.h"

//****************************************************
// PointLight Class Definition
//****************************************************

PointLight::PointLight(Coordinate* pos, Color* col) {
    point = pos;
    color = col;
}

Ray* PointLight::generateLightRay(LocalGeo* loc) {
    Vector* vec = loc->getPosition()->vectorTo(point);
    Ray* ray = new Ray(loc->getPosition(),vec);

    // Ray from intersection position to light
    return ray;
}

Vector* PointLight::getLightDirection(Coordinate* pt) {
    Vector* returnVec = point->vectorTo(pt);
    returnVec->normalize();
    return returnVec;
}

