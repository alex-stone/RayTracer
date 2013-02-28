
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
    if (isValidDimensions(h, w)) {
        setImageSize(h, w);
    } else {
        setDefaultImageSize();
    }
}

Scene::Scene(Coordinate ep, Coordinate UL, Coordinate UR, Coordinate LR, Coordinate LL, int h, int w) {
    setEyePosition(ep);
    setCorners(UL, UR, LR, LL);
    if (isValidDimensions(h, w)) {
        setImageSize(h, w);
    } else {
        setDefaultImageSize();
    }
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
    if (isValidDimensions(h, w)) {
        pixelHeight = h;
        pixelWidth = w;
    }
}

void setDefaultCoordinates() {
    ep = new Coordinate(0, 0, 0);
    upperLeft = new Coordinate(-1, 1, -1);
    upperRight = new Coordinate(1, 1, -1);
    lowerRight = new Coordinate(1, -1, -1);
    lowerLeft= new Coordinate(-1, -1, -1);
}

void setDefaultImageSize() {
    pixelHeight = 480;
    pixelWidth = 640;
}

bool isValidDimensions(int h, int w) {
    return (h >= 480 && h <= 2000) && (w >= 640 && w<= 2000);
}


//****************************************************
// Main Render Loop
// 	Sampler   - Generate Sample
// 	Camera    - Generate Ray
// 	RayTracer - Calculate Color
//	Film      - Commit that Color to that Sample
//****************************************************








