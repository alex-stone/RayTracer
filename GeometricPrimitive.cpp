#include <iostream>
#include "GeometricPrimitive.h"
#include "Shape.h"
#include "Intersection.h"
#include "Ray.h"
#include "BRDF.h"
#include "Coordinate.h"
#include "Transformation.h"

//****************************************************
// GeometricPrimitive Class Definition
//****************************************************


GeometricPrimitive::GeometricPrimitive(Shape* shap, BRDF* colorCoefficients, Transformation* trans) {
    shape = shap;
    brdfCoefficients = colorCoefficients;
    Transformation* worldToObj = trans;

}

Intersection* GeometricPrimitive::intersect(Ray* ray) {
    //Ray objRay = worldToObj(ray);
    LocalGeo* loc = this->shape->intersect(ray); //switch with objRay;
    
    if(loc == NULL) {
        return NULL;
    }

    //Transform objLoc to worldLoc

    // Distance = distance from origin of ray to localGeo position.
    float dist = ray->getPosition()->distTo(loc->getPosition());   
    GeometricPrimitive* self = this;

    Intersection* in = new Intersection(self, loc, dist); 

    return in; 

} 

bool GeometricPrimitive::intersectP(Ray* ray) {
    //Ray* objRay = worldToObj(ray);

    return shape->intersectP(ray);  // Change to objRay

}

BRDF* GeometricPrimitive::getBRDF() {
    return brdfCoefficients;
}




