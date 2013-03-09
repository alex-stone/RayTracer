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
    Light** lights;
    int recurseDepth;
    int lightCount;
    int shapeCount;

  public:
    RayTracer();
    RayTracer(Light** lightArray, GeometricPrimitive** primitiveArray, int numLights, int numShapes, int depth);

    //Note: Does the Ray Tracer save the objects or the Scene?

    Intersection* closestIntersection(Ray* ray);

    // Phong Shading Functions
    Vector* reflectedVector(Vector* lightDir, Vector* normal);

    Color* ambientValue(Light* light, Color* ka);
    Color* diffuseValue(Light* light, Vector* lightDir, Vector* normal, Color* kd);
    Color* specularValue(Light* light, Vector* view, Vector* reflectDir, Color* ks);

    Color* getColorFromIntersect(Intersect* inter);
    Color* getSingleLightColor(Intersect* inter, Light* light);


    bool isLightBlocked(Intersect* inter, Light* light);

    Color* trace(Ray* ray, int depth);

};

#endif
