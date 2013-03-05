#ifndef SPHERE_H
#define SPHERE_H

#include "Shape.h"
#include "BRDF.h"

//****************************************************
// Sphere Header Definition
//****************************************************

class Sphere : public Shape {
  private:
    BRDF* colorCoefficients;
    Coordinate* center;
    float radius;
  public:
    Sphere(Coordinate* cent, float rad);
    Sphere(Coordinate* cent, float rad, BRDF* colors);

    LocalGeo* intersect(Ray* ray);
    Vector* getNormal(Coordinate* pos);

    void setDefaultBRDF();
    BRDF* getBRDF(){ return colorCoefficients; };

};

#endif
