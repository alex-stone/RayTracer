#ifndef SHAPE_H
#define SHAPE_H

//****************************************************
// Shape Header Definition
//****************************************************

class Shape {
  public:
    virtual LocalGeo* intersect(Ray* ray) = 0;
    virtual Vector* getNormal(Coordinate* pos) = 0;

};

#endif
