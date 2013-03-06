#include <iostream>
#include "Intersection.h"
#include "GeometricPrimitive.h"
#include "LocalGeo.h"

//****************************************************
// Intersection Class Definition
//****************************************************

Intersection::Intersection(GeometricPrimitive* p, LocalGeo* geo, float tdist) {
    this->primitive = p;
    this->localGeo = geo;
    this->dist = tdist;
}


