#include <iostream>
#include <math.h>
#include "Matrix.h"
#include <Eigen/Dense>

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

TransformMatrix::TransformMatrix(float[4][4] matrix) {
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
//    mat[row][col] = value;
     mat(row, col) = value;

}

TransformMatrix* TransformMatrix::translationMatrix(float x, float y, float z) {
     Matrix* matrix = new Matrix();

     matrix->setValue(0, 3, x);
     matrix->setValue(1, 3, y);
     matrix->setValue(2, 3, z);

     return matrix;
}

TransformMatrix* TransformMatrix::scaleMatrix(float x, float y, float z) {
    Matrix* matrix = new Matrix();

    matrix->setValue(0, 0, x);
    matrix->setValue(1, 1, x);
    matrix->setValue(2, 2, x);
    
    return matrix;
}



TransformMatrix* TransformMatrix::rotationMatrix(float x, float y, float z, float angle) {
    Matrix* matrix = new Matrix();
    Vector* test = new Vector(x, y , z);
    test->normalize();

    float u = test->getX();
    float v = test->getY();
    float w = test->getZ();

/*
    // Check it correct angle for phef
    mat[0][0] = pow(u, 2) + (pow(v, 2) + pow(w, 2))*cos(angle);
    mat[0][1] = u*v(1 - cos(angle))-w*sin(angle);
    mat[0][2] = u*w(1 - cos(angle))+ v*sin(angle)l 
    mat[0][3] = (a(v*v + w*w) -  
    mat[1][0] =
    mat[1][1] = pow(u, 2) + (pow(v, 2) + pow(w, 2))*cos(angle)
    mat[1][2] = 
    mat[1][3] = 
    mat[2][0] = 
    mat[2][1] =
    mat[2][2] -
    mat[2][3=
    mat[3][0] = 
    mat[3][1] = 
    mat[3][2];
    mat[3][3]'
*/


}

void TransformMatrix::print() {
    std::cout << mat << std::endl;
}

int main(int argc, char* argv[]) {
	Matrix* tempMat = new Matrix();
	tempMat->print();	
}
