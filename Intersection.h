#ifndef INTERSECTION_H
#define INTERSECTION_H

#include "Shape.h"
#include "LocalGeo.h"

//****************************************************
// Intersection Header Definition
//****************************************************

class Intersection {
  private:
    Shape* shape;
    LocalGeo* localGeo;
    float dist;

  public:
    Intersection(Shape* s, LocalGeo* geo, float tdist);
   
    // Getter Functions 
    Shape* getShape() { return shape; };
    LocalGeo* getLocalGeo() { return localGeo; };
    float getDist() { return dist };

};

#endif
