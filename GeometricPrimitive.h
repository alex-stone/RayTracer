#ifndef GEOPRIMITIVE_H
#define GEOPRIMITIVE_H

#include "Shape.h"
#include "BRDF.h"
#include "Ray.h"
#include "Intersection.h"

//****************************************************
// GeometricPrimitive Header Definition
//****************************************************

class GeometricPrimitive {
  private:
    Shape* shape;
    BRDF* brdfCoefficients;

  public:
    GeometricPrimitive(Shape* shap, BRDF* colorCoefficients);

    Intersection* intersect(Ray* ray);
    bool intersectP(Ray* ray);

    BRDF* getBRDF();

};


#endif

