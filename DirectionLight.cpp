#include <iostream>
#include <math.h>

#include "DirectionLight.h"
#include "Vector.h"
#include "Coordinate.h"
#include "Color.h"
#include "Ray.h"

//****************************************************
// Direction Light Class Definition
//****************************************************

DirectionLight::DirectionLight(Vector* dir, Color* col) {
    direction = dir;
    color = col;
}

Ray* DirectionLight::generateLightRay(LocalGeo* loc) {
    Vector* vec = direction->getCopy();
    vec->scale(-1);
    Ray* ray = new Ray(loc->getPosition(), vec);

    return ray;
}

Vector* DirectionLight::getLightDirection(Coordinate* pt) {
    Vector* returnVec = direction->getCopy();
    returnVec->scale(-1);
    returnVec->normalize(); 
    return returnVec;
}
