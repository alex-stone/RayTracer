#ifndef SCENE_H
#define SCENE_H

#include <iostream>
#include "Coordinate.h"
#include "Film.h"
#include "Sampler.h"
#include "Sample.h"

//****************************************************
// Scene Header Definition
//****************************************************

class Scene {
  private:
    Coordinate* eyePosition;
    Coordinate* upperLeft;
    Coordinate* upperRight;
    Coordinate* lowerRight;
    Coordinate* lowerLeft;
    int pixelHeight;
    int pixelWidth;
    
    Sampler* sceneSampler;
    Film* sceneFilm;

    void initializeSampleFilm(int h, int w);

    void setDefaultSampleFilm();
    void setDefaultCoordinates();
    void setDefaultImageSize();

    bool isValidDimensions(int h, int w);

  public:
    Scene();
    Scene(int h, int w);
    Scene(Coordinate* ep, Coordinate* UL, Coordinate* UR, Coordinate* LR, Coordinate* LL, int h, int w);
  
    void setEyePosition(Coordinate* ep); 
    void setCorners(Coordinate* UL, Coordinate* UR, Coordinate* LR, Coordinate* LL);
    void setImageSize(int height, int width);

    Coordinate* getUL() {return upperLeft; };
    Coordinate* getUR() {return upperRight; };
    Coordinate* getLR() {return lowerRight; };
    Coordinate* getLL() {return lowerLeft; };

    int getHeight() {return pixelHeight; };
    int getWidth() {return pixelWidth; };

};

#endif
