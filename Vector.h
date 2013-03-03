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

    void normalize();
    void scale(float s);

    void add(Vector v);
    void sub(Vector v);
    float dot(Vector v);

}
