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
    worldToObj = trans->getCopy();
}

Intersection* GeometricPrimitive::intersect(Ray* ray) {


    Ray* objRay = ray->applyInverseTransformation(worldToObj);
    
    // Local object
    LocalGeo* objLoc = this->shape->intersect(objRay); //switch with objRay;
    
    if(objLoc == NULL) {
        return NULL;
    }

    //LocalGeo* loc = objLoc->applyTransformation(worldToObj);

    //Transform objLoc to worldLoc

    // Distance = distance from origin of ray to localGeo position.
    float dist = ray->getPosition()->distTo(objLoc->getPosition());   
    GeometricPrimitive* self = this;


    Intersection* in = new Intersection(self, objLoc, dist); 

    return in; 

} 

bool GeometricPrimitive::intersectP(Ray* ray) {
    Ray* objRay = ray->applyTransformation(worldToObj);

    return shape->intersectP(objRay);  // Change to objRay

}

BRDF* GeometricPrimitive::getBRDF() {
    return brdfCoefficients;
}




