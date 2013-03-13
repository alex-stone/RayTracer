#ifndef MATRIX_H
#define MATRIX_H

//****************************************************
// Matrix Header Definition
//****************************************************

#include "Eigen/Dense"
#include "Coordinate.h"
#include "Vector.h"

using namespace Eigen;

class TransformMatrix {
  private:
    //float mat[4][4];
    Eigen::Matrix<float,4,4> mat;

    Eigen::Matrix4f getAntisymmetricMatrix(Vector* vec);

  public:
    TransformMatrix();
    TransformMatrix(float** matrix);
    TransformMatrix(Matrix4f matrix);

    TransformMatrix* translationMatrix(float x, float y, float z);
    TransformMatrix* scaleMatrix(float x, float y, float z);
    TransformMatrix* rotateMatrix(float x, float y, float z, float angle);

    Eigen::Matrix<float,4,4> getMatrix() {return mat; };


    Eigen::Matrix4f vectorTimesTranspose(Vector* vec);
    TransformMatrix* inverse();

    // multMatrix - Right Multiply
    void multMatrix(TransformMatrix* matrix);
    // multInverseMatrix - Left Multiply
    void multInverseMatrix(TransformMatrix* matrix);

    void setValue(int row, int col, float value);

    
    Coordinate* transformPt(Coordinate* pt);
//    Coordinate* inverseTransformPt(Coordinate* pt);
    Vector* transformVec(Vector* vec);
  //  Vector* inverseTransformVec(Vector* vec);
    void print();
};



#endif
