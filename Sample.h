#include <iostream>

class Sample {
  private:
    float x, y;

  public:
    Sample();
    Sample(float a, float b);
    
    void getX() {return x; }
    void getY() {return y; }

    // No Set Functions, because a Sample's don't change coordinates
}

