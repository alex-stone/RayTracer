
#include <iostream>

#include "Scene.h"
#include "Sampler.h"
#include "Coordinate.h"
#include "Film.h"

#include <time.h>
#include <math.h>

//****************************************************
// Scene Class 
//****************************************************

Scene::Scene() {
    setDefaultCoordinates();
    setDefaultImageSize(); 
    setDefaultSampleFilm(); 
    setDefaultRayTracer();
}

Scene::Scene(int h, int w) {
    setDefaultCoordinates();
    setDefaultRayTracer();
    if (isValidDimensions(h, w)) {
        setImageSize(h, w);
	initializeSampleFilm(h, w);
    } else {
        setDefaultImageSize();
	setDefaultSampleFilm();
    }
}

Scene::Scene(Coordinate* ep, Coordinate* UL, Coordinate* UR, Coordinate* LR, Coordinate* LL, int h, int w) {
    setEyePosition(ep);
    setCorners(UL, UR, LR, LL);
    setDefaultRayTracer();
    if (isValidDimensions(h, w)) {
        setImageSize(h, w);
	initializeSampleFilm(h, w);
    } else {
        setDefaultImageSize();
	setDefaultSampleFilm();
    }
}

Scene::Scene(Coordinate* ep, Coordinate* UL, Coordinate* UR, Coordinate* LR, Coordinate* LL, int h, int w, Primitive** primitives) {
    setEyePosition(ep);
    setCorners(UL, UR, LR, LL);
    if (isValidDimensions(h, w)) {
  	setImageSize(h,w);
        initializeSampleFilm(h,w);
    } else {
	setDefaultImageSize();
	setDefaultSampleFilm();
    }
    setRayTracer(primitives);
}

void Scene::setEyePosition(Coordinate* ep) {
    eyePosition = ep;
}

void Scene::setCorners(Coordinate* UL, Coordinate* UR, Coordinate* LR, Coordinate* LL) {
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

void Scene::setRayTracer(Primitive** primitives) {
    sceneTracer = new RayTracer(primitives, 1);
}

void Scene::setDefaultRayTracer() {
    Shape* sphere = new Sphere(new Coordinate(0, 0, -2), 1);    

    BRDF* brdf = new BRDF(0.2f, 0.5f, 0.5f);

    Primitive* primitives[1];
    primitives[0] = new Primitive(sphere, brdf)

    sceneTracer = new RayTracer(primitives, 1);
}

void Scene::initializeSampleFilm(int h, int w) {
    sceneSampler = new Sampler(h, w);
    sceneFilm = new Film(h, w);
}

void Scene::setDefaultSampleFilm() {
    sceneSampler = new Sampler(480, 640);
    sceneFilm = new Film(480, 640);
}

void Scene::setDefaultCoordinates() {
    eyePosition = new Coordinate(0.0f, 0.0f, 0.0f);
    upperLeft = new Coordinate(-1.0f, 1.0f, -1.0f);
    upperRight = new Coordinate(1.0f, 1.0f, -1.0f);
    lowerRight = new Coordinate(1.0f, -1.0f, -1.0f);
    lowerLeft= new Coordinate(-1.0f, -1.0f, -1.0f);
}

void Scene::setDefaultImageSize() {
    pixelHeight = 480;
    pixelWidth = 640;
}

bool Scene::isValidDimensions(int h, int w) {
    return (h >= 480 && h <= 2000) && (w >= 640 && w<= 2000);
}


//****************************************************
// Main Render Loop
// 	Sampler   - Generate Sample
// 	Camera    - Generate Ray
// 	RayTracer - Calculate Color
//	Film      - Commit that Color to that Sample
//****************************************************

void render() {


}



