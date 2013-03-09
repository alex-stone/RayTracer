#include <iostream>
#include "RayTracer.h"

//****************************************************
// RayTracer Class Definition
//****************************************************

RayTracer::RayTracer() {
    // Generate a generic sphere
    recurseDepth = 1;
}

RayTracer::RayTracer(GeometricPrimitive** primitiveArray, int depth) {
    primitives = primitiveArray;
    recurseDepth = depth;

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
 * 
 */
Color* RayTracer::getSingleLightColor(Intersect* inter, Light* light) {
    Color* color = new Color(0.0f, 0.0f, 0.0f);

    if(light->isPointLight()) {
	lightDir 

    } else {


    }


}

Color* RayTracer::getColorFromIntersect(Intersect* inter) {
    Color* color = new Color(0.0f, 0.0f, 0.0f);

    // Iterate Through all the Lights




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

