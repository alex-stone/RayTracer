
#include <iostream>

#include "Scene.h"
#include "Shape.h"
#include "Sphere.h"
#include "Sampler.h"
#include "Camera.h"
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
    setDefaultCamera();
}

Scene::Scene(int h, int w) {
    setDefaultCoordinates();
    setDefaultRayTracer();
    if (isValidDimensions(h, w)) {
        setImageSize(h, w);
	initializeSampleFilm(h, w);
        setCameraSize(h, w);
    } else {
        setDefaultImageSize();
	setDefaultSampleFilm();
   	setDefaultCamera();
    }
}

Scene::Scene(Coordinate* ep, Coordinate* UL, Coordinate* UR, Coordinate* LR, Coordinate* LL, int h, int w) {
    setEyePosition(ep);
    setCorners(UL, UR, LR, LL);
    setDefaultRayTracer();
    if (isValidDimensions(h, w)) {
        setImageSize(h, w);
	initializeSampleFilm(h, w);
	setCamera(ep, UL, UR, LR, LL, h, w);
    } else {
        setDefaultImageSize();
	setDefaultSampleFilm();
	setCameraCoordinates(ep, UL, UR, LR, LL);
    }
}

Scene::Scene(Coordinate* ep, Coordinate* UL, Coordinate* UR, Coordinate* LR, Coordinate* LL, int h, int w, GeometricPrimitive** primitives) {
    setEyePosition(ep);
    setCorners(UL, UR, LR, LL);
    if (isValidDimensions(h, w)) {
  	setImageSize(h,w);
        initializeSampleFilm(h,w);
	setCamera(ep, UL, UR, LR, LL, h, w);	
    } else {
	setDefaultImageSize();
	setDefaultSampleFilm();
	setCameraCoordinates(ep, UL, UR, LR, LL);
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

void Scene::setCameraSize(int h, int w) {
    eyePosition = new Coordinate(0.0f, 0.0f, 0.0f);
    upperLeft = new Coordinate(-1.0f, 1.0f, -1.0f);
    upperRight = new Coordinate(1.0f, 1.0f, -1.0f);
    lowerRight = new Coordinate(1.0f, -1.0f, -1.0f);
    lowerLeft= new Coordinate(-1.0f, -1.0f, -1.0f);

    sceneCamera = new Camera(eyePosition, upperLeft, upperRight, lowerRight, lowerLeft, h, w);
}

void Scene::setCameraCoordinates(Coordinate* ep, Coordinate* UL, Coordinate* UR, Coordinate* LR, Coordinate* LL) {
    sceneCamera = new Camera(ep, UL, UR, LR, LL, 480, 640);

}

void Scene::setCamera(Coordinate* ep, Coordinate* UL, Coordinate* UR, Coordinate* LR, Coordinate* LL, int h, int w) {
    sceneCamera = new Camera(ep, UL, UR, LR, LL, h, w);
}
void Scene::setDefaultCamera() {
    setCameraSize(480, 640);
}

void Scene::setRayTracer(GeometricPrimitive** primitives) {
    sceneTracer = new RayTracer(primitives, 1);
}

void Scene::setDefaultRayTracer() {
    Shape* sphere = new Sphere(new Coordinate(0, 0, -2), 1);    

    Color* kd = new Color(0.3f, 0.3f, 0.3f);
    Color* ks = new Color(0.2f, 0.6f, 0.2f);
    Color* ka = new Color(0.0f, 0.4f, 0.3f);
    Color* kr = new Color(0.2f, 0.2f, 0.2f);

    BRDF* brdf = new BRDF(kd, ks, ka, kr);

    GeometricPrimitive** primitives = new GeometricPrimitive*[1];
    primitives[0] = new GeometricPrimitive(sphere, brdf);

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

void Scene::render() {
    Sample* sample = sceneSampler->getSample(0,0);    
    Ray* ray;
    Color* color;

    while(sample != NULL) {
	
    	ray = sceneCamera->generateRay(sample);
	color = sceneTracer->trace(ray, 1);
	sceneFilm->commit(sample, color);	
	sample = sceneSampler->getNextSample(sample);
    }

    sceneFilm->writeImage();

}


int main(int argc, char* argv[]) {

    Coordinate* eye = new Coordinate(0.0f, 0.0f, 0.0f);
    Coordinate* UL = new Coordinate(-1.0f, 1.0f, 0.0f);
    Coordinate* UR = new Coordinate(1.0f, 1.0f, -2.0f);
    Coordinate* LR = new Coordinate(1.0f, -1.0f, -2.0f);
    Coordinate* LL = new Coordinate(-1.0f, -1.0f, 0.0f);


    Shape* sphere = new Sphere(new Coordinate(0.0f, 0.0f, -2.0f), 1);

    Color* kd = new Color(0.3f, 0.3f, 0.3f);
    Color* ks = new Color(0.2f, 0.6f, 0.2f);
    Color* ka = new Color(0.0f, 0.4f, 0.3f);
    Color* kr = new Color(0.2f, 0.2f, 0.2f);

    BRDF* brdf = new BRDF(kd, ks, ka, kr);


    GeometricPrimitive** primitives = new GeometricPrimitive*[1];
    primitives[0] = new GeometricPrimitive(sphere, brdf);


    Scene* scene = new Scene(eye, UL, UR, LR, LL, 640, 640, primitives);

    scene->render();
}



