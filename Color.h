#include <iostream>


//****************************************************
// Color Header Definition
//****************************************************

class Color {
  private:
    float r, g, b;

  public:
    Color();
    Color(float x, float y, float z);

    float getR() {return r; };
    float getG() {return g; };
    float getB() {return b; };

    float clipValue(float x);

};

