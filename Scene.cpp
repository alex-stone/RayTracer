
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

#include "Scene.h"
#include "Shape.h"
#include "Sphere.h"
#include "Triangle.h"
#include "Sampler.h"
#include "Camera.h"
#include "Coordinate.h"
#include "Film.h"
#include "Light.h"
#include "DirectionLight.h"
#include "PointLight.h"

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

Scene::Scene(Coordinate* ep, Coordinate* UL, Coordinate* UR, Coordinate* LR, Coordinate* LL, int h, int w, Light** lights, GeometricPrimitive** primitives, int lightCount, int shapeCount) {
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
    setRayTracer(lights, primitives, lightCount, shapeCount);
    
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

void Scene::setRayTracer(Light** lights, GeometricPrimitive** primitives, int lightCount, int shapeCount) {
    sceneTracer = new RayTracer(lights, primitives, lightCount, shapeCount, 1);
}

void Scene::setDefaultRayTracer() {
    Shape* sphere = new Sphere(new Coordinate(0, 0, -2), 1);    

    Color* kd = new Color(0.3f, 0.3f, 0.3f);
    Color* ks = new Color(0.2f, 0.6f, 0.2f);
    Color* ka = new Color(0.0f, 0.4f, 0.3f);
    Color* kr = new Color(0.2f, 0.2f, 0.2f);

    BRDF* brdf = new BRDF(kd, ks, ka, kr);

    Coordinate* lightPt = new Coordinate(-2.0f, 2.0f, -8.0f);
    Color* lightColor = new Color(0.5f, 0.5f, 0.0f);

    Light** lights = new Light*[1];
    lights[0] = new PointLight(lightPt, lightColor);
    int lightCount = 1;

    GeometricPrimitive** primitives = new GeometricPrimitive*[1];
    primitives[0] = new GeometricPrimitive(sphere, brdf);
    int shapeCount = 1;

    int depth = 1;

    sceneTracer = new RayTracer(lights, primitives, lightCount, shapeCount, depth);
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
    Coordinate* UL = new Coordinate(-1.0f, 1.0f, -3.0f);
    Coordinate* UR = new Coordinate(1.0f, 1.0f, -3.0f);
    Coordinate* LR = new Coordinate(1.0f, -1.0f, -3.0f);
    Coordinate* LL = new Coordinate(-1.0f, -1.0f, -3.0f);

    int width = 680;
    int height = 680;


    Shape* sphere1 = new Sphere(new Coordinate(0.0f, 0.0f, -20.0f), 3.0f);
    Color* ka1 = new Color(0.1f, 0.1f, 0.1f);
    Color* kd1 = new Color(1.0f, 0.0f, 1.0f);
    Color* ks1 = new Color(1.0f, 1.0f, 1.0f);
    Color* kr1 = new Color();
    BRDF* brdf1 = new BRDF(kd1, ks1, ka1, kr1);

    Shape* sphere2 = new Sphere(new Coordinate(-2.0f, 2.0f, -15.0f), 1.0f);
    Color* ka2 = new Color(0.1f, 0.1f, 0.1f);
    Color* kd2 = new Color(1.0f, 1.0f, 0.0f);
    Color* ks2 = new Color(1.0f, 1.0f, 1.0f);
    Color* kr2 = new Color();
    BRDF* brdf2 = new BRDF(kd2, ks2, ka2, kr2);

    Shape* sphere3 = new Sphere(new Coordinate(-2.0f, -2.0f, -15.0f), 1.0f); 
    Color* ka3 = new Color(0.1f, 0.1f, 0.1f);
    Color* kd3 = new Color(0.0f, 1.0f, 1.0f);
    Color* ks3 = new Color(1.0f, 1.0f, 1.0f);
    Color* kr3 = new Color();
    BRDF* brdf3 = new BRDF(kd3, ks3, ka3, kr3);

    // Triangle 1
    Coordinate* v1 = new Coordinate(5.0f, 5.0f, -17.0f);
    Coordinate* v2 = new Coordinate(1.0f, 4.0f, -20.0f);
    Coordinate* v3 = new Coordinate(6.0f, -1.0f, -20.0f);
    Shape* triangle1 = new Triangle(v1, v2, v3);
    Color* ka4 = new Color(0.1f, 0.1f, 0.1f);
    Color* kd4 = new Color(0.1f, 0.1f, 0.1f);
    Color* ks4 = new Color(1.0f, 1.0f, 1.0f);
    Color* kr4 = new Color(1.0f, 1.0f, 1.0f);
    BRDF* brdf4 = new BRDF(kd4, ks4, ka4, kr4);

    Vector* dir1 = new Vector(0.57735027f, -0.57735027f, -0.57735027f);
    Color* col1 = new Color(1.0f, 1.0f, 1.0f);
    DirectionLight* light1 = new DirectionLight(dir1, col1);
    
    Vector* dir2 = new Vector(0.57735027f, 0.57735027f, -0.57735027f);
    Color* col2 = new Color(0.0f, 0.0f, 1.0f);
    DirectionLight* light2 = new DirectionLight(dir2, col2);

    int shapeCount = 4;
    GeometricPrimitive** primitives = new GeometricPrimitive*[3]; 
    primitives[0] = new GeometricPrimitive(sphere1, brdf1);
    primitives[1] = new GeometricPrimitive(sphere2, brdf2);
    primitives[2] = new GeometricPrimitive(sphere3, brdf3);
    primitives[3] = new GeometricPrimitive(triangle1, brdf4);

    int lightCount = 2;
    Light** lights = new Light*[2];
    lights[0] = light1;
    lights[1] = light2; 



/*
    // Case 1: Diffuse Sphere w/ Directional Light
    Shape* sphere1 = new Sphere(new Coordinate(0.0f, 0.0f, -2.0f), 1);
   
    Color* kd = new Color(1.0f, 0.0f, 1.0f);
    Color* ka = new Color();
    Color* ks = new Color(0.0f, 0.0f, 0.0f);
    Color* kr = new Color();    
 
    Coordinate* pt = new Coordinate(1.0f, 1.0f, 1.0f);
    Color* col = new Color(1.0f, 1.0f, 1.0f);
    PointLight* light = new PointLight(pt, col);

    int lightCount = 1;
    int shapeCount = 1;

    BRDF* brdf = new BRDF(kd, ks, ka, kr);

    Light** lights = new Light*[lightCount];
    lights[0] = light;    

    GeometricPrimitive** primitives = new GeometricPrimitive*[shapeCount];
    primitives[0] = new GeometricPrimitive(sphere1, brdf);


    // Case 3 Shading:
    //	Two Lights - Directional and Point
    Shape* sphere = new Sphere(new Coordinate(0.0f, 0.0f, -2.0f), 1);

    Color* kd = new Color(0.521f, 0.72f, 0.2f);
    Color* ks = new Color(0.214f, 0.621f, 0.623f);
    Color* ka = new Color(0.0f, 0.0f, 0.0f);
    Color* kr = new Color(0.2f, 0.2f, 0.2f);

    BRDF* brdf = new BRDF(kd, ks, ka, kr);

    Vector* vec = new Vector(-0.5f, 0.1234f, -0.42f);
    Color* col = new Color(0.235f, 0.263f, 0.233);
    DirectionLight* light1 = new DirectionLight(vec, col);

    Coordinate* pt = new Coordinate(1.512f, 1.123f, 1.123f);
    Color* col2 = new Color(0.125, 0.643, 0.6423);
    PointLight* light2 = new PointLight(pt, col2);

    int lightCount = 2;
    int shapeCount = 1;

    Light** lights = new Light*[lightCount];
    lights[0] = light1;
    lights[1] = light2;

    GeometricPrimitive** primitives = new GeometricPrimitive*[1];
    primitives[0] = new GeometricPrimitive(sphere, brdf);
    PointLight* light1 = new PointLight(new Coordinate(0.0f, 4.0f, 8.0f), new Color(0.4f, 0.4f, 0.0f)); 
 
    Light** lights = new Light*[1];
    lights[0] = light1;
*/
    Scene* scene = new Scene(eye, UL, UR, LR, LL, height, width, lights, primitives, lightCount, shapeCount);

    scene->render();
}



