#include <iostream>
#include "Sphere.h"
#include "BRDF.h"
#include "LocalGeo.h"

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

    Vector* rayDir = ray->getDirection();
    Vector* rayOrigin = ray->getPosition()->vectorFromOrigin();

    float a = rayDir->dot(rayDir);
    float b = (rayDir->dot(rayOrigin)) * 2;
    float c = rayOrigin->dot(rayOrigin) - pow(this->radius, 2);

    float discriminant = pow(b, 2) - 4*a*c;
    float t;

    if(discriminant < 0) { 
	return NULL;
    }
 
    Coordinate* intersectPoint;

    float t1 = 0.0f;
    float t2 = 0.0f;

    if(discriminant == 0) {
	t1 = (-b) / (2*a);
        t2 = NULL;
    } else {
	t1 = (-b + sqrt(discriminant)) / (2*a);
        t2 = (-b - sqrt(discriminant)) / (2*a);
    }

    if(t2 == NULL) {
    	if(t1 > 0) {
	    t = t1;
	} else {
	    return NULL;
	}
    }

    // First determine which float is smaller, then check if they're positive
    if(t1 > t2) {
        float temp = t2;
        t2 = t1;
        t1 = temp; 
    } 

    // We know t2 > t1, so if t2 < 0, then they both are
    if (t2 < 0) {
	return NULL;
    }
 
    if (t1 < 0) {
	t = t2;
    } else {
	t = t1;
    }
 
    intersectPoint = rayOrigin->addVector(rayDir->scale(t));
    Vector* normal = 

    LocalGeo* loc = new LocalGeo(intersectPoint, this->getNormal(intersectPoint));

    return loc;
}

Vector* Sphere::getNormal(Coordinate* pos) {
    return center->vectorTo(pos).normalize();

}


void Sphere::setDefaultBRDF() {
    Color* kd = new Color(0.3f, 0.3f, 0.3f);
    Color* ka = new Color(0.2f, 0.5f, 0.0f);
    Color* ks = new Color(0.6f, 0.6f, 0.6f);
    Color* kr = new Color(0.3f, 0.3f, 0.3f);

    colorCoefficients = new BRDF(kd, ka, ks, kr);
}




