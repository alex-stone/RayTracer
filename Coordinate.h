#ifndef COORDINATE_H
#define COORDINATE_H

#include "Vector.h"

//****************************************************
// Coordinate Header Definition
//****************************************************

class Coordinate {
  private:
    float x, y, z;

  public:
    Coordinate();
    Coordinate(float a, float b, float c);

    void setCoordinate(float a, float b, float c);
    float getX() {return x; };
    float getY() {return y; };
    float getZ() {return z; };

    // Add any other functions needed

    Vector* vectorTo(Coordinate* pos);
 
    void print();
    Coordinate* getCopy();
};

#endif
