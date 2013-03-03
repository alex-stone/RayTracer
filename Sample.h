#include <iostream>

class Sample {
  private:
    int x, y;

  public:
    Sample();
    Sample(int a, int b);
    
    int getX() {return x; }
    int getY() {return y; }

    // No Set Functions, because a Sample's don't change coordinates
};

