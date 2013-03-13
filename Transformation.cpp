#include <iostream>
#include <iostream>
#include "Eigen/Dense"
#include "Transformation.h"
#include "TransformMatrix.h"


//****************************************************
// Transformation Class Definition
//****************************************************

Transformation::Transformation() {
    mat = new TransformMatrix();
    inverseMatrix = new TransformMatrix();
}


// Right Multiplies the Matrix and left Multiplies the inverse Matrix to current inverseMatrix;
// thus maintaining inverseMatrix, as the inverse of the overall matrix
void Transformation::addMatrix(TransformMatrix* matrix) {
    mat->multMatrix(matrix);
    inverseMatrix->multInverseMatrix(matrix->inverse());
}

void Transformation::translate(float x, float y, float z) {
    //
    TransformMatrix* translate = mat->translationMatrix(x, y, z);
    this->addMatrix(translate);

}

void Transformation::scale(float x, float y, float z) {
    TransformMatrix* scale = mat->scaleMatrix(x, y, z);

    this->addMatrix(scale);
}

void Transformation::rotate(float x, float y, float z, float angle) {
    TransformMatrix* rotate = mat->rotateMatrix(x, y, z, angle);
    this->addMatrix(rotate);
}

void Transformation::print() {
    this->mat->print();
}

Transformation* Transformation::getCopy() {
    Transformation* returnTransform = new Transformation();
    TransformMatrix* m = new TransformMatrix(this->getMatrix()->getMatrix());
    returnTransform->addMatrix(m);
    return returnTransform;   
}
/*
int main(int argc, char* argv[]) {
    Transformation* transform = new Transformation(); 
    transform->print();
    transform->translate(3.0f, 0.0f, 0.0f);
    transform->print();
    transform->scale(2.0f, 5.0f, 1.0f);
    transform->print();


    Eigen::Matrix<float,4,4> matrix4f ;

    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) {
            matrix4f(i,j) = 4*i+j;
        }
    }        


    TransformMatrix* matrix1 = transform->getMatrix();
    Eigen::Matrix<float,4,4> m1 = matrix1->getMatrix();
    
    TransformMatrix* matrix1Inverse = transform->getInverseTransformation();
    Eigen::Matrix<float,4,4> m2 = matrix1Inverse->getMatrix();

    std::cout << matrix4f << std::endl;
    matrix4f = matrix4f * m1;
   
    std::cout << matrix4f << std::endl;
    matrix4f = matrix4f * m2; 

    std::cout << matrix4f << std::endl;
}*/


