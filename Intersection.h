#ifndef INTERSECTION_H
#define INTERSECTION_H

//#include "GeometricPrimitive.h"
#include "LocalGeo.h"
class GeometricPrimitive;

//****************************************************
// Intersection Header Definition
//****************************************************

class Intersection {
  private:
    GeometricPrimitive* primitive;
    LocalGeo* localGeo;
    float dist;

  public:
    Intersection(GeometricPrimitive* p, LocalGeo* geo, float tdist);
   
    // Getter Functions 
    GeometricPrimitive* getPrimitive() { return primitive; };
    LocalGeo* getLocalGeo() { return localGeo; };
    float getDist() { return dist; };

};

#endif
