
#include <iostream>

#include "Scene.h"

#include <time.h>
#include <math.h>


// Scene Constructor
Scene::Scene() {
    setDefaultCoordinates();
    setDefaultImageSize(); 

}

Scene::Scene(int h, int w) {
    setDefaultCoordinates();
    setImageSize(h, w);
}

Scene::Scene(Coordinate ep, Coordinate UL, Coordinate UR, Coordinate LR, Coordinate LL, int h, int w) {
    setEyePosition(ep);
    setCorners(UL, UR, LR, LL);
    setImageSize(h, w,);

}

void Scene::setEyePosition(Coordinate ep) {
    eyePosition = ep;
}

void Scene::setCorners(Coordinate UL, Coordinate UR, Coordinate LR, Coordinate LL) {
    upperLeft = UL;
    upperRight = UR;
    lowerRight = LR;
    lowerLeft = LL;
}

void Scene::setImageSize(int h, int w) {
    pixelHeight = h;
    pixelWidth = w;
}


//****************************************************
// Main Render Loop
// 	Sampler   - Generate Sample
// 	Camera    - Generate Ray
// 	RayTracer - Calculate Color
//	Film      - Commit that Color to that Sample
//****************************************************








