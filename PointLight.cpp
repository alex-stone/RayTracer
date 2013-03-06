#include <iostream>
#include <math.h>

#include "Coordinate.h"
#include "Color.h"
#include "Vector.h"

//****************************************************
// PointLight Class Definition
//****************************************************

PointLight::PointLight(Coordinate* pos, Color* col) {
    this->point = pos;
    this->color = col;
}

Ray* PointLight::generateLightRay(LocalGeo *loc) {
    Vector* vec = loc->getPosition().vectorTo(this->point);
    Ray* ray = new Ray(loc->getPosition(),vec);

    // Ray from intersection position to light
    return ray;
}



