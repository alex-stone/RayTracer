#ifndef TRANSFORMATION_H
#define TRANSFORMATION_H

#include "Eigen/Dense"
#include "TransformMatrix.h"
#include "Ray.h"
#include "Coordinate.h"
#include "Vector.h"
#include "Light.h"

//****************************************************
// Transformation Header Definition
//****************************************************

class Transformation {
  private:
    TransformMatrix* mat;
    TransformMatrix* inverseMatrix;
  public:
    Transformation(); // Create Identity Matrix?
    
    // Adds a Transformation onto it
    void addMatrix(TransformMatrix* matrix);
    
    TransformMatrix* getMatrix() { return mat; };
    TransformMatrix* getInverseTransformation() { return inverseMatrix; };

    void translate(float x, float y, float z);
    void scale(float x, float y, float z);
    void rotate(float x, float y, float z, float angle); 

    Coordinate* pointToObject(Coordinate* pt);
    Coordinate* pointToWorld(Coordinate* pt);

    Ray* rayToObject(Ray* ray);
    Ray* rayToWorld(Ray* ray);

    Light* lightToObject(Light* light);
    Light* lightToWorld(Light* light);

    Vector* vectorToObject(Vector* vec);
    Vector* vectorToWorld(Vector* vec);

    Vector* normalToObject(Vector* vec);
    Vector* normalToWorld(Vector* vec);


    Coordinate* transformPt(Coordinate* pt);
    Vector* transformVec(Vector* vec);

    void print();

    Transformation* getCopy();
};

#endif
