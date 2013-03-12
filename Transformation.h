#ifndef TRANSFORMATION_H
#define TRANSFORMATION_H

#include <Eigen/Dense>
#include "TransformMatrix.h"

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
 
    void print();

    

};

#endif
