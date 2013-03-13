#include <iostream>
#include "Intersection.h"
#include "GeometricPrimitive.h"
#include "LocalGeo.h"

//****************************************************
// Intersection Class Definition
//****************************************************

Intersection::Intersection(GeometricPrimitive* p, LocalGeo* geo, float distWorld, float distObj) {
    this->primitive = p;
    this->localGeo = geo;
    this->worldDist = distWorld;
    this->objDist = distObj;
}
/*
LocalGeo* Intersection::getWorldGeo() {
    LocalGeo* worldLoc = localGeo->applyInverseTransformation(primitive->getTransformation());

    return worldLoc;
}*/
