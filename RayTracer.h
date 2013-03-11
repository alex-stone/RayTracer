#ifndef RAYTRACER_H
#define RAYTRACER_H

#include "Ray.h"
#include "Shape.h"
#include "Color.h"
#include "GeometricPrimitive.h"
#include "Light.h"
#include "Intersection.h"

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
    Color* specularValue(Light* light, Vector* viewDir, Vector* reflectDir, Color* ks, float sp);

    Color* getColorFromIntersect(Intersection* inter, Vector* viewDir, int depth);
    Color* getSingleLightColor(Intersection* inter, Vector* viewDir, Light* light, int depth);


    bool isLightBlocked(Intersection* inter, Light* light);

    Color* trace(Ray* ray, int depth);

};

#endif
