#ifndef SCENE_H
#define SCENE_H

#include <iostream>
#include "Coordinate.h"
#include "Film.h"
#include "Camera.h"
#include "Sampler.h"
#include "Sample.h"
#include "RayTracer.h"
#include "GeometricPrimitive.h"
#include "Intersection.h" 
#include "Light.h"

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
    Camera* sceneCamera;

    RayTracer* sceneTracer;

    void initializeSampleFilm(int h, int w);

    void setDefaultSampleFilm();
    void setDefaultCoordinates();
    void setDefaultImageSize();

    bool isValidDimensions(int h, int w);

  public:
    Scene();
    Scene(int h, int w);
 
    Scene(Coordinate* ep, Coordinate* UL, Coordinate* UR, Coordinate* LR, Coordinate* LL, int h, int w);
    Scene(Coordinate* ep, Coordinate* UL, Coordinate* UR, Coordinate* LR, Coordinate* LL, int h, int w, Light** lights, GeometricPrimitive** primitives, int lightCount, int shapeCount, int depth);
 
    void setEyePosition(Coordinate* ep); 
    void setCorners(Coordinate* UL, Coordinate* UR, Coordinate* LR, Coordinate* LL);
    void setImageSize(int height, int width);

    void setCameraSize(int h, int w);
    void setCameraCoordinates(Coordinate* ep, Coordinate* UL, Coordinate* UR, Coordinate* LR, Coordinate* LL);
    void setCamera(Coordinate* ep, Coordinate* UL, Coordinate* UR, Coordinate* LR, Coordinate* LL, int h, int w);
    void setDefaultCamera();

    void setRayTracer(Light** lights, GeometricPrimitive** primitives, int lightCount, int shapeCount, int depth);
    void setDefaultRayTracer();

    Coordinate* getUL() {return upperLeft; };
    Coordinate* getUR() {return upperRight; };
    Coordinate* getLR() {return lowerRight; };
    Coordinate* getLL() {return lowerLeft; };

    int getHeight() {return pixelHeight; };
    int getWidth() {return pixelWidth; };

    Scene* loadTestFromDiary();
    void loadScene(std::string file);

    void render();

};

#endif
