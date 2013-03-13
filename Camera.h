#ifndef CAMERA_H
#define CAMERA_H

#include "Coordinate.h"
#include "Sample.h"
#include "Vector.h"
#include "Ray.h"


//****************************************************
// Camera Header Definitions
//****************************************************

class Camera {
  private:
    Coordinate* eyePosition;
    Coordinate* upperLeft;
    Coordinate* upperRight;
    Coordinate* lowerRight;
    Coordinate* lowerLeft;

    int pixelHeight;
    int pixelWidth;

  public:
    Camera(int h, int w);
    Camera(Coordinate* ep, Coordinate* UL, Coordinate* UR, Coordinate* LR, Coordinate* LL, int h, int w);
    Camera(Coordinate* lookfrom, Coordinate* lookat, Vector* up, float fovVert, int h, int w);

    Vector* pixelToVector(int x, int y);

    Ray* generateRay(Sample* samp);

    void printCameraInfo();
};

#endif
