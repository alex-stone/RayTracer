#include <iostream>

//****************************************************
// Camera Header Definitions
//****************************************************

class Camera {
  private:
    Coordinate eyePosition;
    Coordinate upperLeft;
    Coordinate upperRight;
    Coordinate lowerRight;
    Coordinate lowerLeft;

    int pixelHeight;
    int pixelWidth;

  public:
    Camera();
    Camera(Coordinate ep, Coordinate UL, Coordinate UR, Coordinate LR, Coordinate LL, int h, int w);


    Coordinate pixelToCoordinate(int h, int w);

    Ray generateRay(Sample samp);

}
