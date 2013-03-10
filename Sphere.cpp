#include <iostream>
#include <math.h>
#include "Sphere.h"
#include "LocalGeo.h"
#include "Coordinate.h"
#include "Vector.h"
#include "Ray.h"

//****************************************************
// Sphere Class Definition
//****************************************************

Sphere::Sphere(Coordinate* cent, float rad) {
    center = cent;
    radius = rad;
}


//****************************************************
// Intersect: Uses the Quadratic Formula
//	- Test if discrimant:
//      - <0 misses sphere
//      - =0 intersects tangentially
//	- >0 intersects twice
//****************************************************
LocalGeo* Sphere::intersect(Ray* ray) {
    // This Ray is converted into Object Space

    // At^2 + Bt + C = 0
    // A = (dir . dir)
    // B = 2 (dir . ray origin)
    // C = (ray origin . ray origian) - r^2


    Vector* rayToCenter = ray->getPosition()->vectorTo(center);
    rayToCenter->normalize();

    // Test Angle between rayDir and origin to center of sphere

    Vector* rayDir = ray->getDirection();

    // Vector vecToCenter from Origin to Sphere Center
    Vector* vecToCenter = ray->getPosition()->vectorTo(center);

    // float centerProj  vecToCenter projected onto rayDirection
    float centerProj = vecToCenter->dot(rayDir);
    if(centerProj < 0.0f) {
        return NULL;
    }

    float distToRaySquared = vecToCenter->dot(vecToCenter) - (centerProj * centerProj);

    // float distToRay: Pythagorean Theorem wiht vectProjCenter and vecToCenter
    if(distToRaySquared < 0) {
        return NULL;
    }
  
    float distToRay = sqrt(distToRaySquared);

    if(distToRay > this->radius) {
        return NULL;
    }

    // float pointToProjCenter: Pythagorean Theorem with Radius and distToRay
    float pointToProjCenter = sqrt((this->radius * this->radius) - (distToRay * distToRay));

    float t1 = centerProj - pointToProjCenter;
    float t2 = centerProj + pointToProjCenter;

    Vector* temp = rayDir->getCopy();
    temp->scale(t1);
    

    Coordinate* surfacePoint = ray->getPosition()->addVector(temp);
    Vector* normal = this->center->vectorTo(surfacePoint);
    LocalGeo* loc = new LocalGeo(surfacePoint, normal);

    return loc;

}

bool Sphere::intersectP(Ray* ray) {
    Vector* rayDir = ray->getDirection();
    Vector* rayOrigin = ray->getPosition()->vectorFromOrigin();

    float a = rayDir->dot(rayDir);
    float b = (rayDir->dot(rayOrigin)) * 2.0f;
    float c = rayOrigin->dot(rayOrigin) - pow(this->radius, 2);

    float discriminant = pow(b, 2) - 4.0f*a*c;

    return (discriminant >= 0.0f);
}

Vector* Sphere::getNormal(Coordinate* pos) {
    Vector* vec = center->vectorTo(pos);
    vec->normalize();
    return vec;
}





