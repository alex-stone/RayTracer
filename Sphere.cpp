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
    setDefaultBRDF();

}

Sphere::Sphere(Coordinate* cent, float rad, BRDF* colors) {
    center = cent;
    radius = rad;
    colorCoefficients = colors;
}


//****************************************************
// Intersect: Uses the Quadratic Formula
//	- Test if discrimant:
//      - <0 misses sphere
//      - =0 intersects tangentially
//	- >0 intersects twice
//****************************************************
LocalGeo* Sphere::intersect(Ray* ray) {

    // Convert Ray to Object's POV

    // At^2 + Bt + C = 0
    // A = (dir . dir)
    // B = 2 (dir . ray origin)
    // C = (ray origin . ray origian) - r^2

    discriminant 


}

Vector* Sphere::getNormal(Coordinate* pos) {


}


void Sphere::setDefaultBRDF() {
    Color* kd = new Color(0.3f, 0.3f, 0.3f);
    Color* ka = new Color(0.2f, 0.5f, 0.0f);
    Color* ks = new Color(0.6f, 0.6f, 0.6f);
    Color* kr = new Color(0.3f, 0.3f, 0.3f);

    colorCoefficients = new BRDF(kd, ka, ks, kr);
}




