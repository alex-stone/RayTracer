#include <iostream>
#include <math.h>
#include <float.h>
#include "Ray.h"
#include "Transformation.h"

//****************************************************
// Ray Class - Note, may want to use one Ray, and keep
//		Changing its values so as to not have 
//		too many of them
//****************************************************

Ray::Ray(Coordinate* pos, Vector* dir) {
    position = pos->getCopy();
    direction = dir->getCopy();
 
    direction->normalize();
    t_min = 1;
    t_max = FLT_MAX;
     
}

Ray::Ray(Coordinate* pos, Vector* dir, float min, float max) {
    position = pos->getCopy();
    direction = dir->getCopy();

    direction->normalize();
    t_min = min;
    t_max = max;
}

Coordinate* Ray::getPointFromDist(float dist) {
    Vector* dir = direction->getCopy();
    dir->scale(dist);
    
    return position->addVector(dir);
}

Ray* Ray::applyTransformation(Transformation* transform) {
    Coordinate* pos = transform->getMatrix()->transformPt(position);
    Vector* dir = transform->getMatrix()->transformVec(direction);

    Ray* ray = new Ray(pos, dir);
    return ray;
}

Ray* Ray::applyInverseTransformation(Transformation* transform) {
    Coordinate* pos = transform->getInverseTransformation()->transformPt(position);
    Vector* dir = transform->getInverseTransformation()->transformVec(direction);

    Ray* ray = new Ray(pos, dir);
    return ray;
}


/*
int main(int argc, char* argv[]) {
    Coordinate* pos = new Coordinate(0.3f, 0.2f, -0.4f);
    Vector* dir = new Vector(0.9f, 2.0f, 3.0f);
    Ray* r = new Ray(pos, dir);

    // Add functions for Ray as needed.
 
}
*/


