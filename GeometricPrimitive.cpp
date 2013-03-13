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
    transform = trans->getCopy();
}

Intersection* GeometricPrimitive::intersect(Ray* ray) {


    Ray* objRay = transform->rayToObject(ray);

    LocalGeo* objLoc = this->shape->intersect(objRay);

    if(objLoc == NULL) {
        return NULL;
    }

    Coordinate* objSurfacePoint = objLoc->getPosition();
    Coordinate* worldSurfacePoint = transform->pointToWorld(objSurfacePoint);

    float worldDist = ray->getPosition()->distTo(worldSurfacePoint);
    float objDist = objRay->getPosition()->distTo(objSurfacePoint);

    Intersection* in = new Intersection(this, objLoc, worldDist, objDist); 

    return in; 

/*

    Ray* objRay = ray->applyInverseTransformation(worldToObj);
    
    // Local object
    LocalGeo* objLoc = this->shape->intersect(objRay); //switch with objRay;
    
    if(objLoc == NULL) {
        return NULL;
    }

    //LocalGeo* loc = objLoc->applyTransformation(worldToObj);

    //Transform objLoc to worldLoc

    LocalGeo* worldLoc = objLoc->applyTransformation(worldToObj);


    float dist = ray->getPosition()->distTo(worldLoc->getPosition());

    // Distance = distance from origin of ray to localGeo position.
  //  float dist = objRay->getPosition()->distTo(objLoc->getPosition());   


    GeometricPrimitive* self = this;


    // Includes WORLD_DIST

    Intersection* in = new Intersection(self, objLoc, dist); 

    return in; 
*/
}

bool GeometricPrimitive::intersectP(Ray* ray) {
    Ray* objRay = transform->rayToObject(ray);

    return shape->intersectP(objRay);  // Change to objRay

}

BRDF* GeometricPrimitive::getBRDF() {
    return brdfCoefficients;
}




