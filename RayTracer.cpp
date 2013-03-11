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
        std::cout << "Lights Color" << std::endl;
        lights[i]->getColor()->print();
    }

    for(int i = 0; i < numShapes; i++) {
        primitives[i] = primitiveVec.at(i);
        std::cout << "Primitives Color" << std::endl;
        primitives[i]->getBRDF()->getKA()->print();
    }
     
    recurseDepth = depth;
    lightCount = numLights;
    shapeCount = numShapes;

}
Intersection* RayTracer::closestIntersection(Ray* ray) {
    Intersection* closest = NULL;

    for(int i = 0; i< shapeCount; i++) {
	    Intersection* temp = primitives[i]->intersect(ray);
	    if(temp != NULL && temp->getDist() > 0.001f) {
	        if(closest == NULL || (temp->getDist() < closest->getDist())) {
		         closest = temp;
	        }
	    }
    }

    // Note if no intersections found, it remains NULL
    return closest;

} 
//****************************************************
// Check's if there is an object, between the light
// and the point
//****************************************************
bool RayTracer::isLightBlocked(Intersection* inter, Light* light) {
    float distToLight;
    if(light->isPointLight()) {
        distToLight = inter->getLocalGeo()->getPosition()->distTo(light->getPosition());
    } else {
        distToLight = -1.0f;
    }

    Ray* lightRay = light->generateLightRay(inter->getLocalGeo()->getPosition());

    // Iterate thru shapes to check if Shape is blocking
    for(int i = 0; i < shapeCount; i++) {
        // Test that primitive is not blocking itself.
        Intersection* shadowObject = primitives[i]->intersect(lightRay);

        if(shadowObject != NULL && shadowObject->getPrimitive() != inter->getPrimitive()) {
            
            if(!light->isPointLight()) {
                return true;
            } else {
                Intersection* shadowObject = primitives[i]->intersect(light->generateLightRay(inter->getLocalGeo()->getPosition()));
                if(inter->getLocalGeo()->getPosition()->distTo(shadowObject->getLocalGeo()->getPosition()) < distToLight ) {
                    return true;
                }
            }
        }
    }
    return false;
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
    Color* lightColor = light->getColor();

    returnColor->setR(lightColor->getR() * ka->getR());
    returnColor->setG(lightColor->getG() * ka->getG());
    returnColor->setB(lightColor->getB() * ka->getB());

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

/**
 *  
 *    Vector* Normal = inter->getLocalGeo()->getNormal()
 *    Vector* View   = ? From Reflected Vector need to derive.
 *    Vector* lightDir = 
 */
Color* RayTracer::getSingleLightColor(Intersection* inter, Vector* viewDir, Light* light, int depth) {
    Color* color = new Color(0.0f, 0.0f, 0.0f);
    Vector* lightDir;
    Coordinate* surfacePt = inter->getLocalGeo()->getPosition();
    Vector* normal = inter->getLocalGeo()->getNormal();
    BRDF* brdf = inter->getPrimitive()->getBRDF();

    // Vector Direction - From Light to Surface
    lightDir = light->getLightDirection(surfacePt)->getCopy();
    lightDir->normalize();

    // Vector Direction - From Surface to Light
    Vector* objToLightDir = lightDir->getOpposite();

    // Vector Direction - From Surface to Reflect direction then Get Opposite
    Vector* reflectDir = reflectedVector(objToLightDir, normal)->getOpposite();
    
    // Check if Light Is Blocked
    if(!isLightBlocked(inter, light)) {

        //color->add(ambientValue(light, brdf->getKA()));

        // Diffuse Component
        color->add(diffuseValue(light, lightDir, normal, brdf->getKD()));

        // Specular Component
        color->add(specularValue(light, viewDir, reflectDir, brdf->getKS(), brdf->getSP()));
    }

    return color;

}

Color* RayTracer::getColorFromIntersect(Intersection* inter, Vector* viewDir, int depth) {
    Color* color = new Color(0.0f, 0.0f, 0.0f);

    // Iterate Through all the Lights

    // Check if Adding makes the value over 1.0f
    for(int i = 0; i < lightCount; i++) {
        color->add(getSingleLightColor(inter, viewDir, lights[i], depth));
    }

    if (depth == 1) {
    // Ambient Component
  //  color->add(inter->getPrimitive()->getBRDF()->getKA());
}
    color->add(inter->getPrimitive()->getBRDF()->getKA());    

    Coordinate* surfacePt = inter->getLocalGeo()->getPosition();
    Vector* normal = inter->getLocalGeo()->getNormal();

    // Current Ray's Direction
    Vector* reflectDirection = reflectedVector(viewDir, normal);
    reflectDirection->normalize();

    Ray* reflectionRay = new Ray(surfacePt, reflectDirection);
    Color* reflectedValue = trace(reflectionRay, depth+1);

    Color* kr = inter->getPrimitive()->getBRDF()->getKR();
    Color* temp = new Color(reflectedValue->getR()*kr->getR(), reflectedValue->getG()*kr->getG(), reflectedValue->getB()*kr->getB());
    color->add(temp);

    return color;
}

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
    Intersection* closeInter = this->closestIntersection(ray); 

    // Vector Direction from surface Pt to Ray Origin
    Vector* viewDir = ray->getDirection()->getOpposite();

    if(closeInter != NULL) {
	    return getColorFromIntersect(closeInter, viewDir, depth);
    } else {
	    return new Color(0.0f, 0.0f, 0.0f);
    }

}

