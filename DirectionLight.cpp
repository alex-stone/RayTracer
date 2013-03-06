#include <iostream>
#include <math.h>

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

Ray* DirectionLight::generateLightRay(localGeo* loc) {
    Vector* vec = dir;
    Ray* ray = new Ray(loc->getPosition(), vec);

    return ray;
}

