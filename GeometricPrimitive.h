#ifndef GEOPRIMITIVE_H
#define GEOPRIMITIVE_H

#include "Shape.h"
#include "BRDF.h"
#include "Ray.h"
#include "Intersection.h"
#include "Transformation.h"

//****************************************************
// GeometricPrimitive Header Definition
//****************************************************

class GeometricPrimitive {
  private:
    Shape* shape;
    BRDF* brdfCoefficients;
    Transformation* worldToObj;

  public:
    GeometricPrimitive(Shape* shap, BRDF* colorCoefficients, Transformation* trans);

    Intersection* intersect(Ray* ray);
    bool intersectP(Ray* ray);

    BRDF* getBRDF();
    Transformation* getTransformation() {return worldToObj; };
};


#endif

