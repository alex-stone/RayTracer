#ifndef RAY_H
#define RAY_H

#include <iostream>
#include "Vector.h"
#include "Coordinate.h"
#include "Transformation.h"

//****************************************************
// Ray Header Definition 
//	Ray(t) = pos + t*dir
//****************************************************

class Ray {
  private:
    Coordinate* position;
    Vector* direction;
    float t_min, t_max;

  public:
    //Ray();
    Ray(Coordinate* pos, Vector* dir);
    Ray(Coordinate* pos, Vector* dir, float min, float max);
    
    Coordinate* getPosition() { return position; };
    Vector* getDirection() { return direction; }; 
    Coordinate* getPointFromDist(float dist);

    Ray* applyTransformation(Transformation* transform);
    Ray* applyInverseTransformation(Transformation* transform);
};

#endif
