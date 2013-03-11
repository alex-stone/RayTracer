#ifndef MATRIX_H
#define MATRIX_H

//****************************************************
// Matrix Header Definition
//****************************************************

#include <Eigen/Dense>
using namespace Eigen;

class TransformMatrix {
  private:
    //float mat[4][4];
    Eigen::Matrix<float,4,4> mat;

  public:
    TransformMatrix();
    TransformMatrix(float** matrix);
    TransformMatrix(Matrix4f matrix);

    TransformMatrix* translationMatrix(float x, float y, float z);
    TransformMatrix* scaleMatrix(float x, float y, float z);
    TransformMatrix* rotationMatrix(float x, float y, float z, float angle);

    void setValue(int row, int col, float value);


};



#endif
