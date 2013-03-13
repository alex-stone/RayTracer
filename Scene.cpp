
#include <fstream>
#include <sstream>
#include <vector>
#include <stack>
#include <iostream>

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
#include "Transformation.h"

#include <time.h>
#include <math.h>

//****************************************************
// Scene Class 
//****************************************************

Scene::Scene() {
    setDefaultImageSize(); 
    setDefaultSampleFilm(); 
    setDefaultRayTracer();
    setDefaultCamera();
}

Scene::Scene(std::string file) {
    loadScene(file);
}

Scene::Scene(int h, int w) {
    setDefaultRayTracer();
    if (isValidDimensions(h, w)) {
        setImageSize(h, w);
        std::string fname = "output.png";
	    initializeSampleFilm(h, w, fname);
        setCameraSize(h, w);
    } else {
        setDefaultImageSize();
	    setDefaultSampleFilm();
        setDefaultCamera();
    }
}

Scene::Scene(Coordinate* ep, Coordinate* UL, Coordinate* UR, Coordinate* LR, Coordinate* LL, int h, int w, Light** lights, GeometricPrimitive** primitives, int lightCount, int shapeCount, int depth) {
    if (isValidDimensions(h, w)) {
        setImageSize(h,w);
        std::string fname = "output.png";
        initializeSampleFilm(h,w, fname);
        setCamera(ep, UL, UR, LR, LL, h, w);	
    } else {
        setDefaultImageSize();
        setDefaultSampleFilm();
        setCameraCoordinates(ep, UL, UR, LR, LL);
    }
    setRayTracer(lights, primitives, lightCount, shapeCount, depth);
    
}

void Scene::setImageSize(int h, int w) {
    if (isValidDimensions(h, w)) {
        pixelHeight = h;
        pixelWidth = w;
    }
}

void Scene::setCameraSize(int h, int w) {
    Coordinate* eyePosition = new Coordinate(0.0f, 0.0f, 4.0f);
    Coordinate* upperLeft = new Coordinate(-1.0f, 1.0f, 1.0f);
    Coordinate* upperRight = new Coordinate(1.0f, 1.0f, 1.0f);
    Coordinate* lowerRight = new Coordinate(1.0f, -1.0f, 1.0f);
    Coordinate* lowerLeft= new Coordinate(-1.0f, -1.0f, 1.0f);

    sceneCamera = new Camera(eyePosition, upperLeft, upperRight, lowerRight, lowerLeft, h, w);
}

void Scene::setCameraCoordinates(Coordinate* ep, Coordinate* UL, Coordinate* UR, Coordinate* LR, Coordinate* LL) {
    sceneCamera = new Camera(ep, UL, UR, LR, LL, 480, 640);

}

void Scene::setCamera(Coordinate* ep, Coordinate* UL, Coordinate* UR, Coordinate* LR, Coordinate* LL, int h, int w) {
    sceneCamera = new Camera(ep, UL, UR, LR, LL, h, w);
}

void Scene::setCamera(Coordinate* lookfrom, Coordinate* lookat, Vector* up, float fovVert) {
    sceneCamera = new Camera(lookfrom, lookat, up, fovVert, pixelHeight, pixelWidth);
}

void Scene::setDefaultCamera() {
    setCameraSize(480, 640);
}

void Scene::setRayTracer(Light** lights, GeometricPrimitive** primitives, int lightCount, int shapeCount, int depth) {
    sceneTracer = new RayTracer(lights, primitives, lightCount, shapeCount, depth);
}

void Scene::setRayTracer(std::vector<Light*> lights, std::vector<GeometricPrimitive*> primitives, int lightCount, int shapeCount, int depth) {
    sceneTracer = new RayTracer(lights, primitives, lightCount, shapeCount, depth);
}

void Scene::setDefaultRayTracer() {
    Shape* sphere = new Sphere(new Coordinate(0, 0, -2), 1);    

    Color* kd = new Color(0.3f, 0.3f, 0.3f);
    Color* ks = new Color(0.2f, 0.6f, 0.2f);
    Color* ka = new Color(0.0f, 0.4f, 0.3f);
    Color* kr = new Color(0.2f, 0.2f, 0.2f);
    float sp = 20.0f;

    BRDF* brdf = new BRDF(kd, ks, ka, kr, sp);

    Coordinate* lightPt = new Coordinate(-2.0f, 2.0f, -8.0f);
    Color* lightColor = new Color(0.5f, 0.5f, 0.0f);

    Light** lights = new Light*[1];
    lights[0] = new PointLight(lightPt, lightColor);
    int lightCount = 1;

    GeometricPrimitive** primitives = new GeometricPrimitive*[1];
    primitives[0] = new GeometricPrimitive(sphere, brdf, new Transformation());
    int shapeCount = 1;

    int depth = 1;

    sceneTracer = new RayTracer(lights, primitives, lightCount, shapeCount, depth);
}

void Scene::initializeSampleFilm(int h, int w, std::string fname) {
    sceneSampler = new Sampler(h, w);
    sceneFilm = new Film(h, w, fname);
}

void Scene::setDefaultSampleFilm() {
    sceneSampler = new Sampler(480, 640);
    std::string fname = "output.png";
    sceneFilm = new Film(480, 640, fname);
}

void Scene::setDefaultImageSize() {
    pixelHeight = 480;
    pixelWidth = 640;
}

bool Scene::isValidDimensions(int h, int w) {
    return (h >= 480 && h <= 2000) && (w >= 640 && w<= 2000);
}

void Scene::printProgressBar(Sample* sample) {
    if (sample != NULL) {
	     
	    float percent = ((float) sample->getY() /( float) (pixelHeight-1)) * 100;
        int intPercent = (int) percent; 
        std::cout << "Progress: " << intPercent << "%\r";	    
    }
}

void Scene::printCameraInfo() {
    sceneCamera->printCameraInfo();
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
    int count = 0;

    while(sample != NULL) {
		
    	ray = sceneCamera->generateRay(sample);
	    color = sceneTracer->trace(ray, 1);
	    sceneFilm->commit(sample, color);	
	    sample = sceneSampler->getNextSample(sample);
        if(count % 20  == 0) {
            printProgressBar(sample);
        }
        count++;
    }
    std::cout << std::endl;

    sceneFilm->writeImage();

}


Scene* loadSceneTest1() {

    // Given Dist = 1
    float fov = 30.0f;
    float aspectRatio = (float)4/float(3);

    float imageHeight = 2 * tan((fov*3.141592654/180)/2);
    float imageWidth = imageHeight*aspectRatio;

    Coordinate* eye = new Coordinate(0.0f, 0.0f, 1.0f);
    Coordinate* UL = new Coordinate(-imageWidth/2, imageHeight/2, 0.0f);
    Coordinate* UR = new Coordinate(imageWidth/2, imageHeight/2,  0.0f);
    Coordinate* LR = new Coordinate(imageWidth/2, -imageHeight/2, 0.0f);
    Coordinate* LL = new Coordinate(-imageWidth/2, -imageHeight/2, 0.0f);

/*
    Coordinate* eye = new Coordinate(0.0f, 0.0f, 1.0f);
    Coordinate* UL = new Coordinate(-1.0f, 1.0f, -1.0f);
    Coordinate* UR = new Coordinate(1.0f, 1.0f, -1.0f);
    Coordinate* LR = new Coordinate(1.0f, -1.0f, -1.0f);
    Coordinate* LL = new Coordinate(-1.0f, -1.0f, -1.0f);
*/
    Color* ambient = new Color(0.1f, 0.1f, 0.1f);
    Color* diffuse = new Color(1.0f, 0.0f, 0.0f);
    Color* specular = new Color();
    Color* reflective = new Color();
    float spec = 0.0f;

    BRDF* brdf = new BRDF(diffuse, specular, ambient, reflective, spec);

    int width = 640;
    int height = 480;

    Coordinate* p1 = new Coordinate(-1.0f, -1.0f, -5.0f);
    Coordinate* p2 = new Coordinate(1.0f, -1.0f, -5.0f);
    Coordinate* p3 = new Coordinate(1.0f, 1.0f, -5.0f);
    Coordinate* p4 = new Coordinate(-1.0f, 1.0f, -5.0f);

    Shape* tri1 = new Triangle (p1, p2, p3);
    Shape* tri2 = new Triangle (p1, p3, p4);

    Transformation* transform1 = new Transformation();

    GeometricPrimitive* shape1 = new GeometricPrimitive(tri1, brdf, transform1);
    GeometricPrimitive* shape2 = new GeometricPrimitive(tri2, brdf, transform1);


    int shapeCount = 2;
    GeometricPrimitive** primitives = new GeometricPrimitive*[shapeCount];
    primitives[0]=shape1;
    primitives[1]=shape2;

    Coordinate* pos = new Coordinate(4.0f, 0.0f, 4.0f);
    Color* col = new Color(0.5f, 0.5f, 0.5f);
    Light* ptLight = new PointLight(pos, col);
    Vector* vec = new Vector(0.0f, 0.0f, 1.0f);
    Color* col2 = new Color(0.5f, 0.5f, 0.5f);
    Light* dirLight = new DirectionLight(vec, col2);

    int lightCount = 2;
    Light** lights = new Light*[lightCount];
    lights[0] = ptLight;
    lights[1] = dirLight;

    Scene* scene = new Scene(eye, UL, UR, LR, LL, height, width, lights, primitives, lightCount, shapeCount, 1);
    return scene;
}

Scene* loadTestFromDiary2() {
    Coordinate* eye = new Coordinate(0.0f, 0.0f, 0.0f);
    Coordinate* UL = new Coordinate(-1.0f, 1.0f, -3.0f);
    Coordinate* UR = new Coordinate(1.0f, 1.0f, -3.0f);
    Coordinate* LR = new Coordinate(1.0f, -1.0f, -3.0f);
    Coordinate* LL = new Coordinate(-1.0f, -1.0f, -3.0f);

    int width = 1000;
    int height = 1000;

    Vector* dir1 = new Vector(0.57735027f, -0.57735027f, -0.57735027f);
    Color* col1 = new Color(1.0f, 1.0f, 1.0f);
    DirectionLight* light1 = new DirectionLight(dir1, col1);
    
    Vector* dir2 = new Vector(-0.57735027f, 0.57735027f, 0.57735027f);
    Color* col2 = new Color(1.0f, 1.0f, 1.0f);
    DirectionLight* light2 = new DirectionLight(dir2, col2);

    int lightCount = 2;

    Light** lights = new Light*[2];
    lights[0] = light1;
    lights[1] = light2; 

    Shape* sphere1 = new Sphere(new Coordinate(0.0f, 0.0f, -17.0f), 2.0f);
    Color* ka1 = new Color(0.1f, 0.1f, 0.1f);
    Color* kd1 = new Color(1.0f, 0.0f, 0.0f);
    Color* ks1 = new Color(1.0f, 1.0f, 1.0f);
    Color* kr1 = new Color(0.9f, 0.9f, 0.9f);
    float sp1 = 50.0f;
    BRDF* brdf1 = new BRDF(kd1, ks1, ka1, kr1, sp1);
    Transformation* transform1 = new Transformation();
    transform1->scale(4.0f, 2.0f, 2.0f);

    Shape* sphere2 = new Sphere(new Coordinate(0.0f, 4.0f, -17.0f), 1.5f);
    Color* ka2 = new Color(0.1f, 0.1f, 0.1f);
    Color* kd2 = new Color(0.0f, 1.0f, 0.0f);
    Color* ks2 = new Color(1.0f, 1.0f, 1.0f);
    Color* kr2 = new Color(0.9f, 0.9f, 0.9f);
    float sp2 = 50.0f;
    BRDF* brdf2 = new BRDF(kd2, ks2, ka2, kr2, sp2);
    Transformation* transform2 = new Transformation();
    transform2->scale(0.5f, 1.5f, 1.0f);

    Shape* sphere3 = new Sphere(new Coordinate(0.0f, -4.0f, -17.0f), 1.5f);
    Color* ka3 = new Color(0.1f, 0.1f, 0.1f);
    Color* kd3 = new Color(0.0f, 0.0f, 1.0f);
    Color* ks3 = new Color(1.0f, 1.0f, 1.0f);
    Color* kr3 = new Color(0.9f, 0.9f, 0.9f);
    float sp3 = 50.0f;
    BRDF* brdf3 = new BRDF(kd3, ks3, ka3, kr3, sp3);
    Transformation* transform3 = new Transformation();
    transform3->scale(0.5f, 1.5f, 1.0f);

    Shape* sphere4 = new Sphere(new Coordinate(4.0f, 0.0f, -17.0f), 1.5f);
    Color* ka4 = new Color(0.1f, 0.1f, 0.1f);
    Color* kd4 = new Color(1.0f, 1.0f, 0.0f);
    Color* ks4 = new Color(1.0f, 1.0f, 1.0f);
    Color* kr4 = new Color(0.9f, 0.9f, 0.9f);
    float sp4 = 50.0f;
    BRDF* brdf4 = new BRDF(kd4, ks4, ka4, kr4, sp4);
    Transformation* transform4 = new Transformation();
    transform4->scale(0.0f, 1.5f, 1.0f);

    Shape* sphere5 = new Sphere(new Coordinate(-4.0f, 0.0f, -17.0f), 1.5f);
    Color* ka5 = new Color(0.1f, 0.1f, 0.1f);
    Color* kd5 = new Color(0.0f, 1.0f, 1.0f);
    Color* ks5 = new Color(1.0f, 1.0f, 1.0f);
    Color* kr5 = new Color(0.9f, 0.9f, 0.9f);
    float sp5 = 50.0f;
    BRDF* brdf5 = new BRDF(kd5, ks5, ka5, kr5, sp5);
    Transformation* transform5 = new Transformation();
    transform5->scale(0.5f, 1.5f, 1.0f);

    int shapeCount = 5;
    GeometricPrimitive** primitives = new GeometricPrimitive*[shapeCount]; 
    primitives[0] = new GeometricPrimitive(sphere1, brdf1, transform1);
    primitives[1] = new GeometricPrimitive(sphere2, brdf2, transform2);
    primitives[2] = new GeometricPrimitive(sphere3, brdf3, transform3);
    primitives[3] = new GeometricPrimitive(sphere4, brdf4, transform4);
    primitives[4] = new GeometricPrimitive(sphere5, brdf5, transform5);

    Scene* scene = new Scene(eye, UL, UR, LR, LL, height, width, lights, primitives, lightCount, shapeCount, 5);
    return scene;

}

Scene* loadTestFromDiary() {
    Coordinate* eye = new Coordinate(0.0f, 0.0f, 2.0f);
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
    float sp1 = 50.0f;
    BRDF* brdf1 = new BRDF(kd1, ks1, ka1, kr1, sp1);

    Shape* sphere2 = new Sphere(new Coordinate(-2.0f, 2.0f, -15.0f), 1.0f);
    Color* ka2 = new Color(0.1f, 0.1f, 0.1f);
    Color* kd2 = new Color(1.0f, 1.0f, 0.0f);
    Color* ks2 = new Color(1.0f, 1.0f, 1.0f);
    Color* kr2 = new Color();
    float sp2 = 50.0f;
    BRDF* brdf2 = new BRDF(kd2, ks2, ka2, kr2, sp2);

    Shape* sphere3 = new Sphere(new Coordinate(-2.0f, -2.0f, -15.0f), 1.0f); 
    Color* ka3 = new Color(0.1f, 0.1f, 0.1f);
    Color* kd3 = new Color(0.0f, 1.0f, 1.0f);
    Color* ks3 = new Color(1.0f, 1.0f, 1.0f);
    Color* kr3 = new Color();
    float sp3 = 50.0f;
    BRDF* brdf3 = new BRDF(kd3, ks3, ka3, kr3, sp3);

    // Triangle 1
    Coordinate* v1 = new Coordinate(5.0f, 5.0f, -17.0f);
    Coordinate* v2 = new Coordinate(1.0f, 4.0f, -20.0f);
    Coordinate* v3 = new Coordinate(6.0f, -1.0f, -20.0f);
    Shape* triangle1 = new Triangle(v1, v2, v3);
    Color* ka4 = new Color(0.1f, 0.1f, 0.1f);
    Color* kd4 = new Color(0.1f, 0.1f, 0.1f);
    Color* ks4 = new Color(1.0f, 1.0f, 1.0f);
    Color* kr4 = new Color(1.0f, 1.0f, 1.0f);
    float sp4 = 50.0f;
    BRDF* brdf4 = new BRDF(kd4, ks4, ka4, kr4, sp4);

    Vector* dir1 = new Vector(0.57735027f, -0.57735027f, -0.57735027f);
    Color* col1 = new Color(1.0f, 1.0f, 1.0f);
    DirectionLight* light1 = new DirectionLight(dir1, col1);
    
    Vector* dir2 = new Vector(0.57735027f, 0.57735027f, -0.57735027f);
    Color* col2 = new Color(0.0f, 0.0f, 1.0f);
    DirectionLight* light2 = new DirectionLight(dir2, col2);

    Transformation* transform1 = new Transformation();

    int shapeCount = 4;
    GeometricPrimitive** primitives = new GeometricPrimitive*[shapeCount]; 
    primitives[0] = new GeometricPrimitive(sphere1, brdf1, transform1);
    primitives[1] = new GeometricPrimitive(sphere2, brdf2, transform1);
    primitives[2] = new GeometricPrimitive(sphere3, brdf3, transform1);
    primitives[3] = new GeometricPrimitive(triangle1, brdf4, transform1);

    int lightCount = 2;
    Light** lights = new Light*[2];
    lights[0] = light1;
    lights[1] = light2; 

    Scene* scene = new Scene(eye, UL, UR, LR, LL, height, width, lights, primitives, lightCount, shapeCount, 2);
    return scene;
}

void Scene::loadScene(std::string file) {

    // Vectors of Shapes, Lights, and Vertices
    std::vector<GeometricPrimitive*> primitives;
    std::vector<Light*> lights;
    std::vector<Coordinate*> vertices;

    int shapeCount = 0;
    int lightCount = 0;
    int recurseDepth = 5;
 
    // BRDF Color Coefficient initialized with Default Values
    Color* ambient = new Color(0.2f, 0.2f, 0.2f);
    Color* diffuse = new Color(0.0f, 0.0f, 0.0f);
    Color* specular = new Color(0.0f, 0.0f, 0.0f);  
    Color* reflective = new Color(0.0f, 0.0f, 0.0f);
    float shininess = 0.0f;
    Color* emission = new Color(0.0f, 0.0f, 0.0f);


    // Camera Properties
    Coordinate* lookfrom = new Coordinate();
    Coordinate* lookat = new Coordinate();
    Vector* up = new Vector();
    float fovVert = 90;

    // Transformation Stack Initialization
    std::stack<Transformation*> transformations;
    Transformation* identity = new Transformation(); // Make sure this is correct Identity
    transformations.push(identity);

    int lineCount = 0;

    // Default Output File Name
    std::string fname = "output.png";

    std::ifstream inpfile(file.c_str());
    if(!inpfile.is_open()) {
        std::cout << "Unable to open file" << std::endl;
    } else {
        std::string line;
        //MatrixStack mst;

        while(inpfile.good()) {
            std::vector<std::string> splitline;
            std::string buf;

            std::getline(inpfile,line);
            std::stringstream ss(line);

            lineCount++;

            while (ss >> buf) {
                splitline.push_back(buf);
            }
            //Ignore blank lines
            if(splitline.size() == 0) {
                continue;
            }
            //Ignore comments
            if(splitline[0][0] == '#') {
                continue;
            }

            //Valid commands:
            //size width height
            //  must be first command of file, controls image size
            else if(!splitline[0].compare("size")) {

                if(splitline.size() != 3) {
                    std::cout << "File Input Error: " << splitline.size() - 1 << " arguments provided to size on line " << lineCount << ". Requires 2 arguments." << std::endl;
                    std::exit(1);
                }

                int width = atoi(splitline[1].c_str());
                int height = atoi(splitline[2].c_str());

                if(isValidDimensions(height, width)) {
                    pixelWidth = width;
                    pixelHeight = height;
                } else {
                    std::cout << "File Input Error: Size Dimensions Invalid" << std::endl;
                    std::exit(1);
                }

            }
            //maxdepth depth
            //  max # of bounces for ray (default 5)
            else if(!splitline[0].compare("maxdepth")) {
                // maxdepth: atoi(splitline[1].c_str())
            }
            //output filename
            //  output file to write image to 
            else if(!splitline[0].compare("output")) {
                if(splitline.size() != 2) {
                    std::cout << "File Input Error: " << splitline.size() - 1 << " arguments provided to OUTPUT on line " << lineCount << ". Requires 1 arguments." << std::endl;
                    std::exit(1);
                }
                fname = splitline[1];
            }

            //camera lookfromx lookfromy lookfromz lookatx lookaty lookatz upx upy upz fov
            //  speciﬁes the camera in the standard way, as in homework 2.
            else if(!splitline[0].compare("camera")) {
                if(splitline.size() != 11) {
                    std::cout << "File Input Error: " << splitline.size() - 1 << " arguments provided to CAMERA on line " << lineCount << ". Requires 10 arguments." << std::endl;
                    std::exit(1);
                }
               
                lookfrom->setCoordinate(atof(splitline[1].c_str()), atof(splitline[2].c_str()), atof(splitline[3].c_str()));
                lookat->setCoordinate(atof(splitline[4].c_str()), atof(splitline[5].c_str()), atof(splitline[6].c_str()));
                up->setX(atof(splitline[7].c_str()));
                up->setY(atof(splitline[8].c_str()));
                up->setZ(atof(splitline[9].c_str()));
                fovVert = atof(splitline[10].c_str());

            }

            //sphere x y z radius
            //  Deﬁnes a sphere with a given position and radius.
            else if(!splitline[0].compare("sphere")) {
                if(splitline.size() != 5) {
                    std::cout << "File Input Error: " << splitline.size() - 1 << " arguments provided to SPHERE on line " << lineCount << ". Requires 4 arguments." << std::endl;
                    std::exit(1);
                }

                Coordinate* position = new Coordinate(atof(splitline[1].c_str()), atof(splitline[2].c_str()), atof(splitline[3].c_str()));
                float radius = atof(splitline[4].c_str());

                if(radius < 0.0f) {
                    std::cout << "File Input Error: Negative Radius of a Sphere" << std::endl;
                    std::exit(1);
                }
                // Temporarily just Add it, ignoring Transformations
                Shape* sphere = new Sphere(position, radius);
                BRDF* brdf = new BRDF(diffuse, specular, ambient, reflective, shininess);
       

                Transformation* transform = transformations.top()->getCopy();

                GeometricPrimitive* prim = new GeometricPrimitive(sphere, brdf, transform);

                shapeCount += 1;
                primitives.push_back(prim);

            }
            //maxverts number
            //  Deﬁnes a maximum number of vertices for later triangle speciﬁcations. 
            //  It must be set before vertices are deﬁned.
            else if(!splitline[0].compare("maxverts")) {
                if(splitline.size() != 2) {
                    std::cout << "File Input Error: " << splitline.size() - 1 << " arguments provided to MAXVERTS on line " << lineCount << ". Requires 1 arguments." << std::endl;
                    std::exit(1);
                }

                // Care if you want
                // Here, either declare array size
                // Or you can just use a STL vector, in which case you can ignore this
            }
            //maxvertnorms number
            //  Deﬁnes a maximum number of vertices with normals for later speciﬁcations.
            //  It must be set before vertices with normals are deﬁned.
            else if(!splitline[0].compare("maxvertnorms")) {

                // Care if you want
            }
            //vertex x y z
            //  Deﬁnes a vertex at the given location.
            //  The vertex is put into a pile, starting to be numbered at 0.
            else if(!splitline[0].compare("vertex")) {
                if(splitline.size() != 4) {
                    std::cout << "File Input Error: " << splitline.size() - 1 << " arguments provided to VERTEX on line " << lineCount << ". Requires 3 arguments." << std::endl;
                    std::exit(1);
                }


                Coordinate* vert = new Coordinate(atof(splitline[1].c_str()),atof(splitline[2].c_str()),atof(splitline[3].c_str()));
                vertices.push_back(vert);
                
            }
            //vertexnormal x y z nx ny nz
            //  Similar to the above, but deﬁne a surface normal with each vertex.
            //  The vertex and vertexnormal set of vertices are completely independent
            //  (as are maxverts and maxvertnorms).
            else if(!splitline[0].compare("vertexnormal")) {
                // x: atof(splitline[1].c_str()),
                // y: atof(splitline[2].c_str()),
                // z: atof(splitline[3].c_str()));
                // nx: atof(splitline[4].c_str()),
                // ny: atof(splitline[5].c_str()),
                // nz: atof(splitline[6].c_str()));
                // Create a new vertex+normal with these 6 values, store in some array
            }
            //tri v1 v2 v3
            //  Create a triangle out of the vertices involved (which have previously been speciﬁed with
            //  the vertex command). The vertices are assumed to be speciﬁed in counter-clockwise order. Your code
            //  should internally compute a face normal for this triangle.
            else if(!splitline[0].compare("tri")) {
                if(splitline.size() != 4) {
                    std::cout << "File Input Error: " << splitline.size() - 1 << " arguments provided to TRI on line " << lineCount << ". Requires 3 arguments." << std::endl;
                    std::exit(1);
                }

                Coordinate* pt1 = vertices.at(atof(splitline[1].c_str()));
                Coordinate* pt2 = vertices.at(atof(splitline[2].c_str()));
                Coordinate* pt3 = vertices.at(atof(splitline[3].c_str()));
                Shape* triangle = new Triangle(pt1, pt2, pt3);
                BRDF* brdf = new BRDF(diffuse, specular, ambient, reflective, shininess);

                Transformation* transform = transformations.top()->getCopy();


                shapeCount += 1;
                primitives.push_back(new GeometricPrimitive(triangle, brdf, transform));

            }
            //trinormal v1 v2 v3
            //  Same as above but for vertices speciﬁed with normals.
            //  In this case, each vertex has an associated normal, 
            //  and when doing shading, you should interpolate the normals 
            //  for intermediate points on the triangle.
            else if(!splitline[0].compare("trinormal")) {
                // v1: atof(splitline[1].c_str())
                // v2: atof(splitline[2].c_str())
                // v3: atof(splitline[3].c_str())
                // Create new triangle:
                //   Store pointer to array of vertices (Different array than above)
                //   Store 3 integers to index into array
                //   Store current property values
                //   Store current top of matrix stack
            }

            //translate x y z
            //  A translation 3-vector
            else if(!splitline[0].compare("translate")) {
                if(splitline.size() != 4) {
                    std::cout << "File Input Error: " << splitline.size() - 1 << " arguments provided to TRANSLATE on line " << lineCount << ". Requires 3 arguments." << std::endl;
                    std::exit(1);
                }
                transformations.top()->translate(atof(splitline[1].c_str()), atof(splitline[2].c_str()), atof(splitline[3].c_str()));
              
            }
            //rotate x y z angle
            //  Rotate by angle (in degrees) about the given axis as in OpenGL.
            else if(!splitline[0].compare("rotate")) {
                if(splitline.size() != 5) {
                    std::cout << "File Input Error: " << splitline.size() - 1 << " arguments provided to ROTATE on line " << lineCount << ". Requires 4 arguments." << std::endl;
                    std::exit(1);
                }

                transformations.top()->rotate(atof(splitline[1].c_str()), atof(splitline[2].c_str()), atof(splitline[3].c_str()), atof(splitline[3].c_str()));
              
            }
            //scale x y z
            //  Scale by the corresponding amount in each axis (a non-uniform scaling).
            else if(!splitline[0].compare("scale")) {
                if(splitline.size() != 4) {
                    std::cout << "File Input Error: " << splitline.size() - 1 << " arguments provided to SCALE on line " << lineCount << ". Requires 3 arguments." << std::endl;
                    std::exit(1);
                }

                transformations.top()->scale(atof(splitline[1].c_str()), atof(splitline[2].c_str()), atof(splitline[3].c_str()));

            }
            //pushTransform
            //  Push the current modeling transform on the stack as in OpenGL. 
            //  You might want to do pushTransform immediately after setting 
            //   the camera to preserve the “identity” transformation.
            else if(!splitline[0].compare("pushTransform")) {
                if(splitline.size() != 1) {
                    std::cout << "File Input Error: " << splitline.size() - 1 << " arguments provided to PUSHTRANSFORM on line " << lineCount << ". Requires 0 arguments." << std::endl;
                    std::exit(1);
                }

                Transformation* newTransform = transformations.top()->getCopy();
                transformations.push(newTransform);
                //mst.push();
            }
            //popTransform
            //  Pop the current transform from the stack as in OpenGL. 
            //  The sequence of popTransform and pushTransform can be used if 
            //  desired before every primitive to reset the transformation 
            //  (assuming the initial camera transformation is on the stack as 
            //  discussed above).
            else if(!splitline[0].compare("popTransform")) {
                if(splitline.size() != 1) {
                    std::cout << "File Input Error: " << splitline.size() - 1 << " arguments provided to PUSHTRANSFORM on line " << lineCount << ". Requires 0 arguments." << std::endl;
                    std::exit(1);
                }                
                //mst.pop();
                if(transformations.size() <= 1) {
                    std::cout << "File Input Error: PopTransform called without corresponding pushTransform" << std::endl;
                    std::exit(1);
                } else {
                    transformations.pop();
                }
            }

            //directional x y z r g b
            //  The direction to the light source, and the color, as in OpenGL.
            else if(!splitline[0].compare("directional")) {
                // Note this is a vector TOWARDS the directional light
 
                if(splitline.size() != 7) {
                    std::cout << "File Input Error: " << splitline.size() - 1 << " arguments provided to DIRECTIONAL on line " << lineCount << ". Requires 6 arguments." << std::endl;
                    std::exit(1);
                }

                Vector* vec = new Vector(atof(splitline[1].c_str()), atof(splitline[2].c_str()), atof(splitline[3].c_str()));
                Color* col = new Color(atof(splitline[4].c_str()),atof(splitline[5].c_str()),atof(splitline[6].c_str()));

                Light* dirLight = new DirectionLight(vec->getOpposite(), col);

                lightCount += 1; 
                lights.push_back(dirLight);

            }
            //point x y z r g b
            //  The location of a point source and the color, as in OpenGL.
            else if(!splitline[0].compare("point")) {
                if(splitline.size() != 7) {
                    std::cout << "File Input Error: " << splitline.size() - 1 << " arguments provided to POINT on line " << lineCount << ". Requires 6 arguments." << std::endl;
                    std::exit(1);
                }

                Coordinate* pt = new Coordinate(atof(splitline[1].c_str()),  atof(splitline[2].c_str()),  atof(splitline[3].c_str()));
                Color* col = new Color(atof(splitline[4].c_str()),atof(splitline[5].c_str()),atof(splitline[6].c_str()));
                Light* ptLight = new PointLight(pt, col);

                lightCount += 1;
                lights.push_back(ptLight);

            }
            //attenuation const linear quadratic
            //  Sets the constant, linear and quadratic attenuations 
            //  (default 1,0,0) as in OpenGL.
            else if(!splitline[0].compare("attenuation")) {
                // const: atof(splitline[1].c_str())
                // linear: atof(splitline[2].c_str())
                // quadratic: atof(splitline[3].c_str())
            }
            //ambient r g b
            //  The global ambient color to be added for each object 
            //  (default is .2,.2,.2)
            else if(!splitline[0].compare("ambient")) {
                if(splitline.size() != 4) {
                    std::cout << "File Input Error: " << splitline.size() - 1 << " arguments provided to AMBIENT on line " << lineCount << ". Requires 3 arguments." << std::endl;
                    std::exit(1);
                }

                ambient = new Color(atof(splitline[1].c_str()), atof(splitline[2].c_str()), atof(splitline[3].c_str()));

            }

            //diﬀuse r g b
            //  speciﬁes the diﬀuse color of the surface.
            else if(!splitline[0].compare("diffuse")) {
                if(splitline.size() != 4) {
                    std::cout << "File Input Error: " << splitline.size() - 1 << " arguments provided to DIFFUSE on line " << lineCount << ". Requires 3 arguments." << std::endl;
                    std::exit(1);
                }

                diffuse = new Color(atof(splitline[1].c_str()), atof(splitline[2].c_str()), atof(splitline[3].c_str()));

            }
            //specular r g b 
            //  speciﬁes the specular color of the surface.
            else if(!splitline[0].compare("specular")) {
                if(splitline.size() != 4) {
                    std::cout << "File Input Error: " << splitline.size() - 1 << " arguments provided to SPECULAR on line " << lineCount << ". Requires 3 arguments." << std::endl;
                    std::exit(1);
                }

                specular = new Color(atof(splitline[1].c_str()), atof(splitline[2].c_str()), atof(splitline[3].c_str()));
  
            }
            //shininess s
            //  speciﬁes the shininess of the surface.
            else if(!splitline[0].compare("shininess")) {
                if(splitline.size() != 2) {
                    std::cout << "File Input Error: " << splitline.size() - 1 << " arguments provided to SHININESS on line " << lineCount << ". Requires 1 arguments." << std::endl;
                    std::exit(1);
                }

                shininess = atof(splitline[1].c_str());
                if(shininess < 0.0f) {
                    std::cout << "File Input Error: Negative Shininess Value" << std::endl;
                    std::exit(1);
                }

            }
            //emission r g b
            //  gives the emissive color of the surface.
            else if(!splitline[0].compare("emission")) {
                if(splitline.size() != 4) {
                    std::cout << "File Input Error: " << splitline.size() - 1 << " arguments provided to EMISSION on line " << lineCount << ". Requires 3 arguments." << std::endl;
                    std::exit(1);
                }

                emission = new Color(atof(splitline[1].c_str()), atof(splitline[2].c_str()), atof(splitline[3].c_str()));

            } else {
                std::cerr << "Unknown command: " << splitline[0] << std::endl;
            }
        }

        inpfile.close();
    }

    // Initializes the sceneCamera:
    setCamera(lookfrom, lookat, up, fovVert);
    //setDefaultCamera();
    //Initializes the sceneSampler and sceneFilm;
    initializeSampleFilm(pixelHeight, pixelWidth, fname);

    // Initializes the sceneTracer;
    setRayTracer(lights, primitives, lightCount, shapeCount, recurseDepth);


}

Scene* testSphere() {
    Coordinate* eye = new Coordinate(0.0f, 0.0f, 1.0f);
  
    Coordinate* UL = new Coordinate(-1.0f, 1.0f, 0.0f);
    Coordinate* UR = new Coordinate(1.0f, 1.0f, 0.0f);
    Coordinate* LR = new Coordinate(1.0f, -1.0f, 0.0f);
    Coordinate* LL = new Coordinate(-1.0f, -1.0f, 0.0f);


    int width = 680;
    int height = 680;

    Shape* sphere1 = new Sphere(new Coordinate(0.0f, 0.0f, -10.0f), 5.0f);
    Color* ka1 = new Color(0.1f, 0.1f, 0.1f);
    Color* kd1 = new Color(1.0f, 0.0f, 1.0f);
    Color* ks1 = new Color(1.0f, 1.0f, 1.0f);
    Color* kr1 = new Color();
    float sp1 = 50.0f;
    BRDF* brdf1 = new BRDF(kd1, ks1, ka1, kr1, sp1);

    Vector* dir1 = new Vector(0.57735027f, -0.57735027f, -0.57735027f);
    Color* col1 = new Color(1.0f, 1.0f, 1.0f);
    DirectionLight* light1 = new DirectionLight(dir1, col1);
    
    Vector* dir2 = new Vector(0.57735027f, 0.57735027f, -0.57735027f);
    Color* col2 = new Color(0.0f, 0.0f, 1.0f);
    DirectionLight* light2 = new DirectionLight(dir2, col2);

    Transformation* transform1 = new Transformation();
    transform1->scale(1.5f, 1.0f, 1.0f);

    int shapeCount = 1;
    GeometricPrimitive** primitives = new GeometricPrimitive*[shapeCount]; 
    primitives[0] = new GeometricPrimitive(sphere1, brdf1, transform1);


    int lightCount = 2;
    Light** lights = new Light*[2];
    lights[0] = light1;
    lights[1] = light2; 

    Scene* scene = new Scene(eye, UL, UR, LR, LL, height, width, lights, primitives, lightCount, shapeCount, 2);
    return scene;

}


int main(int argc, char* argv[]) {
    Scene* scene;

    if(argc > 1) {
 	      //std::cout << "Test File = " << argv[1] << std::endl;
          scene = new Scene(argv[1]);
    } else {
        //scene = loadTestFromDiary2();
       scene = testSphere();
    }

  //  Scene* scene = loadTestFromDiary();

    scene->render();
}



