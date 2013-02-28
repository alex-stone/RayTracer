
#include <iostream>

class Scene {
  private:
    Coordinate eyePosition;
    Coordinate upperLeft;
    Coordinate upperRight;
    Coordinate lowerRight;
    Coordinate lowerLeft;
    int pixelHeight;
    int pixelWidth;

  public:
    Scene();
    Scene(int h, int w);
    Scene(Coordinate ep, Coordinate UL, Coordinate UR, Coordinate LR, Coordinate LL, int h, int w);
  
    void setEyePosition(Coordinate ep); 
    void setCorners(Coordinate UL, Coordinate UR, Coordinate LR, Coordinate LL);
    void setImageSize(int height, int width);

    Coordinate getUL() {return upperLeft; }
    Coordinate getUR() {return upperRight; }
    Coordinate getLR() {return lowerRight; }
    Coordinate getLL() {return lowerLeft; }


    int getHeight {return pixelHeight; }
    int getWidth {return pixelWidth; }

}
