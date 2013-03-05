#ifndef GEOPRIMITIVE_H
#define GEOPRIMITIVE_H

#include "Primitive.h"
#include "Shape.h"
#include "BRDF.h"
#include "Ray.h"
#include "Intersection.h"

//****************************************************
// GeometricPrimitive Header Definition
//****************************************************

class GeometricPrimitive : public Primitive {
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

