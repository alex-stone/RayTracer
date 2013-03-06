#ifndef PRIMITIVE_H
#define PRIMITIVE_H

#include "Intersection.h"
#include "Ray.h"
#include "BRDF.h"

//****************************************************
// Primitive Header Definition - Abstract
//****************************************************

class Primitive {
  public:
    virtual Intersection* intersect(Ray* ray) = 0;
    virtual bool intersectP(Ray* ray) = 0;
    virtual BRDF* getBRDF() = 0;

};

#endif
