#ifndef RAYTRACER_H
#define RAYTRACER_H

#include "Ray.h"
#include "Shape.h"
#include "Color.h"
#include "GeometricPrimitive.h"

//****************************************************
// RayTracer Header Definition
//****************************************************

class RayTracer {
  private:
    GeometricPrimitive** primitives;
    int recurseDepth;

  public:
    RayTracer();
    RayTracer(GeometricPrimitive** primitiveArray, int depth);

    //Note: Does the Ray Tracer save the objects or the Scene?

    Intersection* closestIntersection(Ray* ray);
    Color* getColorFromIntersect(Intersect* inter);
    Color* getSingleLightColor(Intersect* inter, Light* light);

    bool isLightBlocked(Intersect* inter, Light* light);

    Color* trace(Ray* ray, int depth);

};

#endif
