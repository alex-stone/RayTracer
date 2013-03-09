#include <iostream>
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

    for(int i = 0; i< 1; i++) {
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

bool RayTracer::isLightBlocked(Intersect* inter, Light* light) {


}

/**
 *  Reflected Vector, directed away from the point
 *  R = -L * 2(L dot N)N
 */
Vector* RayTracer::reflectedVector(Vector* lightDir, Vector* normal) {
    float angle = 2*(lightDir->dot(normal));
    Vector* returnVec = new Vector(); 

    returnVec->setX( -(lightDir->getX()) + angle * (normal->getX()) );
    returnVec->setY( -(lightDir->getY()) + angle * (normal->getY()) );
    returnVec->setZ( -(lightDir->getZ()) + angle * (normal->getZ()) );
 
    returnVec->normalize();
    return returnVec;
}

/**
 *  Calculates Ambient Component:  ka * I
 */
Color* RayTracer::ambientValue(Light* light, Color* ka) {
    Color* returnColor = new Color();


    returnColor->setR(light->getR() * ka->getR());
    returnColor->setG(light->getG() * ka->getG());
    returnColor->setB(light->getB() * ka->getB());

    return returnColor;
}

/**
 *  Calculates the Diffuse Component: kd * I * (lightDir dot normal)
 */ 
Color* RayTracer::diffuseValue(Light* light, Vector* lightDir, Vector* normal, Color* kd) {
    Color* returnColor = new Color();

    float intensity = max(lightDir->dot(normal), 0.0f);

    returnColor->setR(light->getR() * kd->getR() * intensity);
    returnColor->setG(light->getG() * kd->getG() * intensity);
    returnColor->setB(light->getB() * kd->getB() * intensity);

    return returnColor; 
}

/**
 *  Calculates the Specular Component: ks * I * (reflectDir dot viewDir) ^ sp
 */ 
Color* RayTracer::specularValue(Light* light, Vector* view, Vector* reflectDir, Color* ks) {
    Color* returnColor = new Color();
    float sp = 1.0f; // FIGURE OUT WHAT VALUE TO SET THIS TO
 
    float intensity = pow( max( reflectDir.dot(view), 0.0f), sp);

    returnColor->setR(light->getR() * ks.getR() * intensity);
    returnColor->setG(light->getG() * ks.getG() * intensity);
    returnColor->setB(light->getB() * ks.getB() * intensity);
 
    return returnColor;
}

/**
 *  
 *    Vector* Normal = inter->getLocalGeo()->getNormal()
 *    Vector* View   = ? From Reflected Vector need to derive.
 *    Vector* lightDir = 
 */
Color* RayTracer::getSingleLightColor(Intersect* inter, Light* light) {
    Color* color = new Color(0.0f, 0.0f, 0.0f);
    Vector* lightDir;
    Coordinate* surfacePt = light->getLocalGeo()->getPosition();
    Vector* normal = light->getLocalGeo()->getNormal();

    BRDF* brdf = inter->getPrimitive()->getBRDF();

    if(light->isPointLight()) {
	lightDir = surfacePt->vectorTo(light->getPoint());
    } else {
        lightDir = light->getDirection()->getCopy();
        lightDir->scale(-1.0f); 
    }

    lightDir->normalize();

    Vector* reflectDir = reflectedVector(lightDir, normal);

    // Ambient Component
    color.add(ambientValue(light brdf->getKA()));

    // Diffuse Component
    color.add(diffuseValue(light, lightDir, normal, brdf->getKD()));

    // Specular Component
    color.add(specularValue(light, view, reflectDir, brdf->getKS()));

    return color;

}

Color* RayTracer::getColorFromIntersect(Intersect* inter) {
    Color* color = new Color(0.0f, 0.0f, 0.0f);

    // Iterate Through all the Lights

    for(int i = 0; i  


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

   if(closeInter != NULL) {
        return colorFromIntersect(closeInter);
    } else {
   	return new Color(0.0f, 0.0f, 0.0f);
    }

}

