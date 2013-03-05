#include <iostream>
#include "Intersection.h"

//****************************************************
// Intersection Class Definition
//****************************************************

Intersection::Intersection(Shape* s, LocalGeo* geo, float tdist) {
    shape = s;
    localGeo = geo;
    dist = tdist;
}


