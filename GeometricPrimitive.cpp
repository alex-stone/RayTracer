#include <iostream>
#include "GeometricPrimitive.h"
#include "Primitive.h"
#include "Shape.h"
#include "Intersection.h"
#include "Ray.h"
#include "BRDF.h"

//****************************************************
// GeometricPrimitive Class Definition
//****************************************************


GeometricPrimitive::GeometricPrimitive(Shape* shap, BRDF* colorCoefficients) {
    shape = shap;
    brdfCoefficients = colorCoefficients;

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
    Primitive* self = this;

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




