#include <iostream>
#include <math.h>
#include <cmath>
#include "RayTracer.h"

//****************************************************
// RayTracer Class Definition
//****************************************************

RayTracer::RayTracer() {
    // Generate a generic sphere
    recurseDepth = 1;
}

RayTracer::RayTracer(Light** lightArray, GeometricPrimitive** primitiveArray, int numLights, int numShapes, int depth) {
    primitives = primitiveArray;
    lights = lightArray;
    recurseDepth = depth;

    lightCount = numLights;    
    shapeCount = numShapes;
} 

Intersection* RayTracer::closestIntersection(Ray* ray) {
    Intersection* closest = NULL;

    for(int i = 0; i< shapeCount; i++) {
	    Intersection* temp = primitives[i]->intersect(ray);
	    if(temp != NULL && temp->getDist() > 0) {
	        if(closest == NULL || (temp->getDist() < closest->getDist())) {
		         closest = temp;
	        }
	    }
    }

    // Note if no intersections found, it remains NULL
    return closest;

} 

bool RayTracer::isLightBlocked(Intersection* inter, Light* light) {


}

/**
 *  Reflected Vector, directed away from the point
 *  R = -L * 2(L dot N)N
 */
Vector* RayTracer::reflectedVector(Vector* lightDir, Vector* normal) {
    float angle = 2*(lightDir->dot(normal));
    Vector* returnVec = new Vector(); 

    returnVec->setX( -lightDir->getX() + (angle * normal->getX()) );
    returnVec->setY( -lightDir->getY() + (angle * normal->getY()) );
    returnVec->setZ( -lightDir->getZ() + (angle * normal->getZ()) );
 
    returnVec->scale(-1.0f);
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
Color* RayTracer::specularValue(Light* light, Vector* viewDir, Vector* reflectDir, Color* ks) {
    Color* returnColor = new Color();
    Color* lightColor = light->getColor();
    float sp = 50.0f; // FIGURE OUT WHAT VALUE TO SET THIS TO
 
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
Color* RayTracer::getSingleLightColor(Intersection* inter, Vector* viewDir, Light* light) {
    Color* color = new Color(0.0f, 0.0f, 0.0f);
    Vector* lightDir;
    Coordinate* surfacePt = inter->getLocalGeo()->getPosition();
    Vector* normal = inter->getLocalGeo()->getNormal();


    BRDF* brdf = inter->getPrimitive()->getBRDF();

    lightDir = light->getLightDirection(surfacePt)->getCopy();

    lightDir->normalize();

    Vector* reflectDir = reflectedVector(lightDir, normal);

    // Ambient Component
    color->add(ambientValue(light, brdf->getKA()));

    // Diffuse Component
    color->add(diffuseValue(light, lightDir, normal, brdf->getKD()));

    // Specular Component
    color->add(specularValue(light, viewDir, reflectDir, brdf->getKS()));

    return color;

}

Color* RayTracer::getColorFromIntersect(Intersection* inter, Vector* viewDir) {
    Color* color = new Color(0.0f, 0.0f, 0.0f);

    // Iterate Through all the Lights

    // Check if Adding makes the value over 1.0f
    for(int i = 0; i < lightCount; i++) {
        color->add(getSingleLightColor(inter, viewDir, lights[i]));
    }

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

    // First Test: if Intersection:
 
    Vector* viewDir = ray->getDirection();

   if(closeInter != NULL) {
        return getColorFromIntersect(closeInter, viewDir);
    } else {
   	    return new Color(0.0f, 0.0f, 0.0f);
    }

}

