#include <iostream>
#include "LocalGeo.h"

//****************************************************
// Local Geo Class Definition
//****************************************************

LocalGeo::LocalGeo(Coordinate* pos, Vector* norm) {
    position = pos;
    norm->normalize();
    normal = norm;
}




