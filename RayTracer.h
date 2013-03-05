#ifndef RAYTRACER_H
#define RAYTRACER_H

#include "Ray.h"
#include "Shape.h"
#include "Color.h"

//****************************************************
// RayTracer Header Definition
//****************************************************

class RayTracer {
  private:
    Shape** shapes;
    int recurseDepth;

  public:
    RayTracer();
    RayTracer(Shape** shapeArray, int depth);

    //Note: Does the Ray Tracer save the objects or the Scene?

    Color* trace(Ray* ray, int depth);



};

#endif
