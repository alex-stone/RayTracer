#include <iostream>
#include <vector>
#include <math.h>
#include <cmath>
#include "RayTracer.h"

//****************************************************
// RayTracer Class Definition
//****************************************************

RayTracer::RayTracer() {
    lights = NULL;
    primitives = NULL;
    lightCount = 0;
    shapeCount = 0;
 
    recurseDepth = 5;
}

RayTracer::RayTracer(Light** lightArray, GeometricPrimitive** primitiveArray, int numLights, int numShapes, int depth) {
    primitives = primitiveArray;
    lights = lightArray;
    recurseDepth = depth;

    lightCount = numLights;    
    shapeCount = numShapes;
} 

RayTracer::RayTracer(std::vector<Light*> lightVec, std::vector<GeometricPrimitive*> primitiveVec, int numLights, int numShapes, int depth) {	
    lights = new Light*[numLights];
    primitives = new GeometricPrimitive*[numShapes];

    for(int i = 0; i < numLights; i++) {
        lights[i] = lightVec.at(i);
    }

    for(int i = 0; i < numShapes; i++) {
        primitives[i] = primitiveVec.at(i);

    }
     
    recurseDepth = depth;
    lightCount = numLights;
    shapeCount = numShapes;

}
Intersection* RayTracer::closestIntersection(Ray* ray) {
    Intersection* closest = NULL;

    for(int i = 0; i< shapeCount; i++) {

    //    GeometricPrimitive* temp = primitives[i];
      //  Ray* objRay = ray->applyInverseTransformation(temp->getTransformation());
	    Intersection* temp = primitives[i]->intersect(ray);

	    if(temp != NULL && temp->getWorldDist() > 0.0001f) {
	        if(closest == NULL || (temp->getWorldDist() < closest->getWorldDist())) {
		         closest = temp;
	        }
	    }
    }

    // Note if no intersections found, it remains NULL
    return closest;

} 

//****************************************************
// Iterate through all the objects to check if there 
//      is an object, between the light and the point 
//      of intersection.
//
// Inputs:
//      Intersection* inter     OBJ reference frame 
//      Light* light            WORLD reference frame
//****************************************************
bool RayTracer::isLightBlocked(Intersection* inter, Light* light) {

    Transformation* transform = inter->getPrimitive()->getTransformation();
  
    Coordinate* objSurfacePoint = inter->getLocalGeo()->getPosition();
    Coordinate* worldSurfacePoint = transform->pointToWorld(objSurfacePoint);

    Light* worldLight = light;

    float distToLight; 

    if(light->isPointLight()) {
        distToLight = worldSurfacePoint->distTo(worldLight->getPosition());
    } else {
        distToLight = -1.0f;
    }


    Ray* worldLightRay = light->generateLightRay(worldSurfacePoint);

    for(int i = 0; i < shapeCount; i++) {

        Intersection* lightBlock = primitives[i]->intersect(worldLightRay);

        // Making sure it isn't accidentally detecting intersection with itself
        if(lightBlock != NULL && lightBlock->getPrimitive() != inter->getPrimitive()) {
            if(light->isPointLight()) {
                if(lightBlock->getWorldDist() < distToLight) {
                    return true;
                }
            } else {
                return true;
            }
        }


    }

    return false;

    /*

    // Distance From Object to Light in WORLD frame
    LocalGeo* worldLocGeo = inter->getWorldGeo();
    Coordinate* worldSurfacePoint = worldLocGeo->getPosition();

    float distToLight; 

    if(light->isPointLight()) {
       // distToLight = worldLoc->getPosition()->distTo(light->getPosition());
        distToLight = worldSurfacePoint->distTo(light->getPosition());
    } else {
        distToLight = -1.0f;
    }

    Ray* worldLightRay = light->generateLightRay(worldSurfacePoint);

    // Iterate thru shapes to check if Shape is blocking
    for(int i = 0; i < shapeCount; i++) {
        // Test that primitive is not blocking itself.

        // Intersection will be in ShadowObject's Reference Frame
        Intersection* shadowObject = primitives[i]->intersect(worldLightRay);

        if(shadowObject != NULL  && shadowObject->getPrimitive() != inter->getPrimitive()) {
            
            if(!light->isPointLight()) {
                return true;
            } else {
                // Intersection's getDist function returns distancei in WORLD frame
                if(shadowObject->getDist() < distToLight ) {
                    return true;
                }
            }
        }
    }
    return false;*/
}

//****************************************************
//  Reflected Vector, directed away from the point
//      R = -L * 2(L dot N)N
//  Note: ONLY USE VECTORS POINTING AWAY FROM SAME PT.    
//****************************************************
Vector* RayTracer::reflectedVector(Vector* lightDir, Vector* normal) {
    float angle = 2*(lightDir->dot(normal));
    Vector* returnVec = new Vector(); 

    returnVec->setX( -lightDir->getX() + (angle * normal->getX()) );
    returnVec->setY( -lightDir->getY() + (angle * normal->getY()) );
    returnVec->setZ( -lightDir->getZ() + (angle * normal->getZ()) );
 
    returnVec->normalize();
    return returnVec;
}

/**
 *  Calculates Ambient Component:  ka * I
 */
Color* RayTracer::ambientValue(Light* light, Color* ka) {
    Color* returnColor = new Color();
   // Color* lightColor = light->getColor();

    // Changing Ambient 

    returnColor->setR(ka->getR());
    returnColor->setG(ka->getG());
    returnColor->setB(ka->getB());

    return returnColor;
}

/**
 *  Calculates the Diffuse Component: kd * I * (lightDir dot normal)
 */ 
Color* RayTracer::diffuseValue(Light* light, Vector* lightDir, Vector* normal, Color* kd) {
    Color* returnColor = new Color();
    Color* lightColor = light->getColor();

    float intensity = std::max(lightDir->dot(normal), 0.0f);

    returnColor->setR(lightColor->getR() * kd->getR() * intensity);
    returnColor->setG(lightColor->getG() * kd->getG() * intensity);
    returnColor->setB(lightColor->getB() * kd->getB() * intensity);

    return returnColor; 
}

/**
 *  Calculates the Specular Component: ks * I * (reflectDir dot viewDir) ^ sp
 */ 
Color* RayTracer::specularValue(Light* light, Vector* viewDir, Vector* reflectDir, Color* ks, float sp) {
    Color* returnColor = new Color();
    Color* lightColor = light->getColor();
 
    //iewDir->setZ(-viewDir->getZ());

    float intensity = pow( std::max( reflectDir->dot(viewDir), 0.0f), sp);

    returnColor->setR(lightColor->getR() * ks->getR() * intensity);
    returnColor->setG(lightColor->getG() * ks->getG() * intensity);
    returnColor->setB(lightColor->getB() * ks->getB() * intensity);
 
    return returnColor;
}


//****************************************************
// Gets the Color contribution from a single light on 
//      a given Intersection. Pass Values to Diffuse
//      and Specular in terms of OBJ frame.
//
// Inputs:
//      Intersection* inter     OBJ reference frame 
//      Vector* viewDir         WORLD reference frame
//      Light* light            WORLD reference frame
//      int depth               Current recursive call
// Variables:
//      worldLight
//      worldViewDir
//      worldNormal
//      worldSurfacePoint
//      worldLightDir
//      worldReflectDir
//****************************************************
Color* RayTracer::getSingleLightColorObj(Intersection* inter, Vector* viewDir, Light* light, int depth) {
    Color* color = new Color(0.0f, 0.0f, 0.0f);
    BRDF* brdf = inter->getPrimitive()->getBRDF();

    Coordinate* objSurfacePoint = inter->getLocalGeo()->getPosition();
    Vector* objNormal = inter->getLocalGeo()->getNormal();
    objNormal->normalize();

    Transformation* transform = inter->getPrimitive()->getTransformation();

    Light* objLight = transform->lightToObject(light);
    Vector* objViewDir = transform->vectorToObject(viewDir);
    objViewDir->normalize();

    Vector* objLightDir = objLight->getLightDirection(objSurfacePoint);
    objLightDir->normalize();

    Vector* objVecToLightDir = objLightDir->getOpposite();
    objVecToLightDir->normalize();

    Vector* objReflectDir = reflectedVector(objLightDir, objNormal)->getOpposite();
    objReflectDir->normalize();

   // Check if Light Is Blocked
    if(!isLightBlocked(inter, light)) {

        //Diffuse Component in OBJ
        color->add(diffuseValue(objLight, objVecToLightDir, objNormal, brdf->getKD()));

        //Specular Component in OBJ
        color->add(specularValue(objLight, objViewDir, objReflectDir, brdf->getKS(), brdf->getSP()));
    }

    return color;

}


Color* RayTracer::getSingleLightColor(Intersection* inter, Vector* viewDir, Light* light, int depth) {
    // Color Variables
    Color* color = new Color(0.0f, 0.0f, 0.0f);
    BRDF* brdf = inter->getPrimitive()->getBRDF();

    Transformation* transform = inter->getPrimitive()->getTransformation();

    Light* worldLight = light;
    Vector* worldViewDir = viewDir;
    worldViewDir->normalize();

    Coordinate* objSurfacePoint = inter->getLocalGeo()->getPosition();
    Coordinate* worldSurfacePoint = transform->pointToWorld(objSurfacePoint);

    Vector* objNormal = inter->getLocalGeo()->getNormal();
    objNormal->normalize();

    Vector* worldNormal = transform->normalToWorld(objNormal);
    worldNormal->normalize();

    Vector* worldLightDir = worldLight->getLightDirection(worldSurfacePoint);
    worldLightDir->normalize();

    Vector* worldVecToLightDir = worldLightDir->getOpposite();
    worldVecToLightDir->normalize();

    Vector* worldReflectDir = reflectedVector(worldLightDir, worldNormal)->getOpposite();
    worldReflectDir->normalize();
/*
    TransformMatrix* worldToObj = inter->getPrimitive()->getTransformation()->getMatrix();
    TransformMatrix* objToWorld = inter->getPrimitive()->getTransformation()->getInverseTransformation();

    // Given: WORLD Reference Fram Variables
    Light* worldLight = light;
    Vector* worldViewDir = viewDir;
    worldViewDir->normalize();

    // Given: OBJ Reference Frame Variables:
    Coordinate* objSurfacePoint = inter->getLocalGeo()->getPosition();
    Vector* objNormal = inter->getLocalGeo()->getNormal();
    objNormal->normalize();

    // Derived: WORLD Reference Frame Variables
    Coordinate* worldSurfacePoint = objToWorld->transformPt(objSurfacePoint);
    Vector* worldNormal = objToWorld->transformVec(objNormal);
    worldNormal->normalize();

    Vector* worldLightDir = worldLight->getLightDirection(worldSurfacePoint);
    worldLightDir->normalize();

    Vector* worldVecToLightDir = worldLightDir->getOpposite();
    worldVecToLightDir->normalize();

    Vector* worldReflectDir = reflectedVector(worldLightDir, worldNormal)->getOpposite();


    // Derived: OBJ Reference Frame Variables
    Light* objLight = worldLight->applyTransform(inter->getPrimitive()->getTransformation());
    Vector* objViewDir = objToWorld->transformVec(worldViewDir);
    objViewDir->normalize();

    Vector* objLightDir = objLight->getLightDirection(objSurfacePoint);
    objLightDir->normalize();

    Vector* objVecToLightDir = objLightDir->getOpposite();
    objVecToLightDir->normalize();

    Vector* objReflectDir = reflectedVector(objLightDir, objNormal)->getOpposite();
    objReflectDir->normalize();
*/
    // Check if Light Is Blocked
    if(!isLightBlocked(inter, light)) {

        // Diffuse Component in WORLD
        color->add(diffuseValue(worldLight, worldVecToLightDir, worldNormal, brdf->getKD()));

        // Specular Component in WORLD
        color->add(specularValue(worldLight, worldViewDir, worldReflectDir, brdf->getKS(), brdf->getSP()));

        // Diffuse Component in OBJ
 //       color->add(diffuseValue(objLight, objVecToLightDir, objNormal, brdf->getKD()));

        // Specular Component in OBJ
//        color->add(specularValue(objLight, objViewDir, objReflectDir, brdf->getKS(), brdf->getSP()));
    }

    return color;

}

//****************************************************
// Gets the Color from a given Intersection, and calls
//      a recursive trace call for reflective rays
// Inputs:
//      Intersection* inter     OBJ reference frame 
//      Vector* viewDir         WORLD reference frame
//      int depth               Current recursive call
//****************************************************

Color* RayTracer::getColorFromIntersect(Intersection* inter, Vector* viewDir, int depth) {
    Color* color = new Color(0.0f, 0.0f, 0.0f);

    // Iterate Through all the Lights

    // Check if Adding makes the value over 1.0f
    for(int i = 0; i < lightCount; i++) {
        color->add(getSingleLightColorObj(inter, viewDir, lights[i], depth));
    }

    Transformation* transform = inter->getPrimitive()->getTransformation();

    // Ambient Component
    color->add(inter->getPrimitive()->getBRDF()->getKA());    

    Vector* worldViewDir = viewDir;
    worldViewDir->normalize();

    // Get the Surface Intersection Point in WORLD Coordinates
    Coordinate* objSurfacePoint = inter->getLocalGeo()->getPosition();
    Coordinate* worldSurfacePoint = transform->pointToWorld(objSurfacePoint);

    Vector* objNormal = inter->getLocalGeo()->getNormal();
    objNormal->normalize();
    Vector* worldNormal = transform->normalToWorld(objNormal);
    worldNormal->normalize();

    Vector* worldReflectDir = reflectedVector(worldViewDir, worldNormal);
    worldReflectDir->normalize();

    Ray* reflectionRay = new Ray(worldSurfacePoint, worldReflectDir);
    Color* reflectedValue = trace(reflectionRay, depth+1);


    // Note Spec for AS2 derives reflectiveness from specularity
    Color* kr = inter->getPrimitive()->getBRDF()->getKS();
    Color* temp = new Color(reflectedValue->getR()*kr->getR(), reflectedValue->getG()*kr->getG(), reflectedValue->getB()*kr->getB());
    color->add(temp);

    return color;
}
/*
    LocalGeo* worldLocGeo = inter->getWorldGeo();
    Coordinate* worldSurfacePoint = worldLocGeo->getPosition();
    Vector* worldNormal = worldLocGeo->getNormal();

    Vector* reflectDirection = reflectedVector(viewDir, worldNormal);
    reflectDirection->normalize();

    Ray* reflectionRay = new Ray(worldSurfacePoint, reflectDirection);
    Color* reflectedValue = trace(reflectionRay, depth+1);


    Color* ks = inter->getPrimitive()->getBRDF()->getKS();
//    Color* kr = inter->getPrimitive()->getBRDF()->getKR();
    Color* temp = new Color(reflectedValue->getR()*ks->getR(), reflectedValue->getG()*ks->getG(), reflectedValue->getB()*ks->getB());
    color->add(temp);

    return color;
}*/

//****************************************************
// Trace Function - Determines Color for a given Ray
//	- Base Case: When depth exceeds recurseDepth
//	- Detect the closest intersection of ray and
//		shape.
//	- Perform Phong Shading on that point
//		- Iterate over all lights
//		- Ignore if light is blocked by another
//			shape.
//		- Add contribution from light
//	- Handle Reflection Rays
//		- Recursive Call to Trace, depth + 1
//		- Add contribution scaled down by the
//			reflective factor
//****************************************************

Color* RayTracer::trace(Ray* ray, int depth) {
    
    // Base Case
    if(depth > recurseDepth) {
        return new Color(0.0f, 0.0f, 0.0f);
    }

    // Detect closest intersection of Ray and Shape:
    // Reference Frame = OBJECT
    Intersection* closeInter = this->closestIntersection(ray); 

    // World: Vector Direction from surface Pt to Ray Origin
    // Reference Frame = WORLD
    Vector* viewDir = ray->getDirection()->getOpposite();
    viewDir->normalize();

   // Vector* viewDir = new Vector(0,0,1);

    if(closeInter != NULL) {
	    return getColorFromIntersect(closeInter, viewDir, depth);
    } else {
	    return new Color(0.0f, 0.0f, 0.0f);
    }

}

