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

Ray* DirectionLight::generateLightRay(Coordinate* pt) {
    Vector* vec = direction->getOpposite();
    Ray* ray = new Ray(pt, vec);
    return ray;
}

Vector* DirectionLight::getLightDirection(Coordinate* pt) {
    Vector* returnVec = direction->getOpposite();
    returnVec->normalize(); 
    return returnVec;
}


