#include <iostream>
#include "RayTracer.h"

//****************************************************
// RayTracer Class Definition
//****************************************************

RayTracer::RayTracer() {
    // Generate a generic sphere
    recurseDepth = 1;
}

RayTracer::RayTracer(shape** shapeArray, int depth) {
    shapes = shapeArray;
    recurseDepth = depth;

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


}

