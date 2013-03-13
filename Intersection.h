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
    float worldDist;
    float objDist;

  public:
    Intersection(GeometricPrimitive* p, LocalGeo* geo, float distWorld, float distObj);
   
    // Getter Functions 
    GeometricPrimitive* getPrimitive() { return primitive; };
    LocalGeo* getLocalGeo() { return localGeo; };
    float getWorldDist() { return worldDist; };
    float getObjDist() { return objDist; };

};

#endif
