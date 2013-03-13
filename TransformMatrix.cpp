#include <iostream>
#include <math.h>
#include "TransformMatrix.h"
#include "Eigen/Dense"
#include "Vector.h"
#include "Coordinate.h"
#include "Vector.h"

//****************************************************
// TransformMatrix Class Definition
//****************************************************

TransformMatrix::TransformMatrix() {

    for(int i = 0; i < 4; i++) {
	    for(int j = 0; j < 4; j++) {
            if(i == j) {
                mat(i,j) = 1.0f;
            } else {
                mat(i,j) = 0.0f;
            } 
        }
    }
}

TransformMatrix::TransformMatrix(float** matrix) {
    for(int i = 0; i < 4; i++) {
	for(int j = 0; j < 4; j++) {
	    mat(i,j) = matrix[i][j];
	}
    }
}

TransformMatrix::TransformMatrix(Matrix4f matrix) {
    mat = matrix;
}

void TransformMatrix::setValue(int row, int col, float value) {
    mat(row, col) = value;

}

TransformMatrix* TransformMatrix::inverse() {
    TransformMatrix* trans = new TransformMatrix(mat.inverse());
    return trans;
}

// Right Multiply
void TransformMatrix::multMatrix(TransformMatrix* matrix) {
     this->mat = this->mat * matrix->getMatrix();
}
// Left Multiply
void TransformMatrix::multInverseMatrix(TransformMatrix* matrix) {
    this->mat = matrix->getMatrix() * this->mat;
}

TransformMatrix* TransformMatrix::translationMatrix(float x, float y, float z) {
     TransformMatrix* matrix = new TransformMatrix();

     matrix->setValue(0, 3, x);
     matrix->setValue(1, 3, y);
     matrix->setValue(2, 3, z);
     matrix->setValue(3,3,1.0f);
     return matrix;
}

TransformMatrix* TransformMatrix::scaleMatrix(float x, float y, float z) {
    TransformMatrix* matrix = new TransformMatrix();

    matrix->setValue(0, 0, x);
    matrix->setValue(1, 1, y);
    matrix->setValue(2, 2, z);
    matrix->setValue(3,3,1.0f);
    
    return matrix;
}

Eigen::Matrix4f TransformMatrix::getAntisymmetricMatrix(Vector* vec) {
    // Creates an array initialize with zeroes
    Eigen::Matrix4f m = Eigen::Matrix4f::Zero();

    vec->normalize();
    float x = vec->getX();
    float y = vec->getY();
    float z = vec->getZ();

    m(0,1) = -z;
    m(0,2) = y;
    m(1,0) = z;
    m(1,2) = -x;
    m(2,0) = -y;
    m(2,1) = x;

    return m;
}

Eigen::Matrix4f TransformMatrix::vectorTimesTranspose(Vector* vec){
    Eigen::Matrix4f returnMatrix = Matrix4f::Zero();
 
    int* arr = new int[3];
    arr[0] = vec->getX();
    arr[1] = vec->getY();
    arr[2] = vec->getZ();

    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            returnMatrix(i,j) = arr[i]*arr[j];
        }
    }

    return returnMatrix;
}


TransformMatrix* TransformMatrix::rotateMatrix(float x, float y, float z, float angle) {
    Vector* test = new Vector(x, y , z);
    test->normalize();

    angle = angle*3.141592654/180;

    Eigen::Matrix4f vecTimesTranspose = vectorTimesTranspose(test);
    Eigen::Matrix4f asymMatrix = getAntisymmetricMatrix(test);

    Eigen::Matrix4f returnMatrix;

    returnMatrix = vecTimesTranspose + (asymMatrix * std::sin(angle)) - (asymMatrix * asymMatrix * std::cos(angle));
    returnMatrix(3,3) = 1;

    //std::cout << returnMatrix << std::endl;

    Eigen::Matrix4f testMatrix = Matrix4f::Zero();
    testMatrix(0,0) = cos(angle);
    testMatrix(1,1) = cos(angle);
    testMatrix(2,2) = cos(angle);

    returnMatrix = testMatrix + (1 - std::cos(angle))*vecTimesTranspose + std::sin(angle)*asymMatrix;
    returnMatrix(3,3) = 1;

    TransformMatrix* result = new TransformMatrix(returnMatrix);
/*
    matrix->setValue(0,0, cos(angle));
    matrix->setValue(0,1, -sin(angle));
    matrix->setValue(1,1, sin(angle));
    matrix->setValue(1,2, cos(angle));
*/

    return result;

}

Coordinate* TransformMatrix::transformPt(Coordinate* pt) {
    Vector4f temp(pt->getX(), pt->getY(), pt->getZ(), 1.0f);
 
    temp = this->mat * temp;


    Coordinate* result =  new Coordinate(temp(0), temp(1), temp(2));
    return result;
}

Vector* TransformMatrix::transformVec(Vector* vec) {
    Vector4f temp(vec->getX(), vec->getY(), vec->getZ(), 0.0f);

    temp = this->mat * temp;

    Vector* result = new Vector(temp(0), temp(1), temp(2));  
    return result;
}



void TransformMatrix::print() {
    std::cout << mat << std::endl;
}

/*
int main(int argc, char* argv[]) {
	TransformMatrix* tempMat = new TransformMatrix();
	tempMat->print();

    Vector* vec = new Vector(1.0f,2.0f,3.0f);
    std::cout << "vector times vectorT" << std::endl;
    std::cout << tempMat->vectorTimesTranspose(vec) << std::endl;

std::cout << "vector times vectorT" << std::endl;

	TransformMatrix* translateMat = tempMat->translationMatrix(0.0f, 0.0f, 2.0f);	
	translateMat->print();


        TransformMatrix* scaleMat = tempMat->scaleMatrix(3.0f, 0.0f, 2.0f);
        scaleMat->print();

        TransformMatrix* rotateMat = tempMat->rotateMatrix(0.0f, 0.0f, 1.0f, 45.0f);
        rotateMat->print();

	TransformMatrix* matrix = new TransformMatrix();

        matrix->setValue(0,0,1.0f);
        matrix->setValue(0,1,2.0f);
        matrix->setValue(0,2,3.0f);
	matrix->setValue(1,0,0.0f);
	matrix->setValue(1,1,1.0f);
	matrix->setValue(1,2,4.0f);
	matrix->setValue(2,0,5.0f);
	matrix->setValue(2,1,6.0f);
	matrix->setValue(2,2,0.0f);

 	matrix->print();
	matrix->inverse()->print();
}*/
