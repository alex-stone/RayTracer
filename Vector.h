#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>

//****************************************************
// Vector Header Definition
//****************************************************

class Vector {
  private:
    float x, y, z;

  public:
    Vector();
    Vector(float a, float b, float c);

    float getX() {return x; };
    float getY() {return y; };
    float getZ() {return z; };
   
    void setX(float a);
    void setY(float b);
    void setZ(float c);

    void normalize();
    void scale(float s);

    void add(Vector* v);
    void sub(Vector* v);
    float dot(Vector* v);
    Vector* cross(Vector* v);

    void print();
    Vector* getCopy();
};

#endif
