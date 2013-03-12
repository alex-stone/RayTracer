#include <iostream>
#include <math.h>
#include "TransformMatrix.h"
#include <Eigen/Dense>
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

     return matrix;
}

TransformMatrix* TransformMatrix::scaleMatrix(float x, float y, float z) {
    TransformMatrix* matrix = new TransformMatrix();

    matrix->setValue(0, 0, x);
    matrix->setValue(1, 1, x);
    matrix->setValue(2, 2, x);
    
    return matrix;
}



TransformMatrix* TransformMatrix::rotateMatrix(float x, float y, float z, float angle) {
    TransformMatrix* matrix = new TransformMatrix();
    Vector* test = new Vector(x, y , z);
    test->normalize();

    float u = test->getX();
    float v = test->getY();
    float w = test->getZ();

    float a = 0.0f;
    float b = 0.0f;
    float c = 0.0f;

    angle = angle*3.141592654/180;

    // Just Rotating about a vector, that goes thru origin so (a, b, c) = (0,0,0)
    // Check it correct angle for phef
    mat(0,0) = pow(u, 2) + (pow(v, 2) + pow(w, 2))*cos(angle);
    mat(0,1) = u*v*(1 - cos(angle))-w*sin(angle);
    mat(0,2) = u*w*(1 - cos(angle))+ v*sin(angle);
    mat(0,3) = (a*(v*v + w*w) - u*(b*v + c*w))*(1 - cos(angle)) + (b*w-c*v)*sin(angle);
    mat(1,0) = u*v*(1 - cos(angle)) + w * sin(angle);
    mat(1,1) = pow(v, 2) + (pow(u, 2) + pow(w, 2))*cos(angle);
    mat(1,2) = v*w*(1 - cos(angle)) - u * sin(angle); 
    mat(1,3) = (b*(pow(u,2) + pow(w,2)) - v*(a*u + c*w))*(1 - cos(angle)) + (c*u - a*w)*sin(angle);
    mat(2,0) = u*w*(1-cos(angle)) - v*sin(angle);
    mat(2,1) = v*w*(1-cos(angle)) + u*sin(angle);
    mat(2,2) = pow(w,2) + (pow(u,2) + pow(v,2))*cos(angle);
    mat(2,3) = (c*(pow(u,2) + pow(w,2)) - w*(a*u + b*v)) * (1 - cos(angle)) + (a*v - b*u)*sin(angle);
    mat(3,0) = 0;
    mat(3,1) = 0;
    mat(3,2) = 0;
    mat(3,3) = 1;


}

void TransformMatrix::print() {
    std::cout << mat << std::endl;
}
/*
int main(int argc, char* argv[]) {
	TransformMatrix* tempMat = new TransformMatrix();
	tempMat->print();

	TransformMatrix* translateMat = tempMat->translationMatrix(0.0f, 0.0f, 2.0f);	
	translateMat->print();


        TransformMatrix* scaleMat = tempMat->scaleMatrix(3.0f, 0.0f, 2.0f);
        scaleMat->print();

        TransformMatrix* rotateMat = tempMat->rotationMatrix(0.0f, 0.0f, 1.0f, 90.0f);
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
