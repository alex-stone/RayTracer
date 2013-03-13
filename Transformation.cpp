#include <iostream>
#include <iostream>
#include "Eigen/Dense"
#include "Transformation.h"
#include "TransformMatrix.h"
#include "Ray.h"
#include "Vector.h"
#include "Coordinate.h"
#include "Light.h"
#include "PointLight.h"
#include "DirectionLight.h"

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

// 4th Position = 1, because we want translations on 
Coordinate* Transformation::pointToObject(Coordinate* pt) {
    Eigen::Matrix4f matrix = mat->getMatrix();
    Eigen::Vector4f temp(pt->getX(), pt->getY(), pt->getZ(), 1.0f);

    temp = matrix * temp;

    return new Coordinate(temp(0), temp(1), temp(2));
}
   
Coordinate* Transformation::pointToWorld(Coordinate* pt) {
    Eigen::Matrix4f matrix = inverseMatrix->getMatrix();
    Eigen::Vector4f temp(pt->getX(), pt->getY(), pt->getZ(), 1.0f);

    temp = matrix * temp;

    return new Coordinate(temp(0), temp(1), temp(2));
}

// For Ray's and Vectors, 4th Position = 0, no translation
Ray* Transformation::rayToObject(Ray* ray) {
    Coordinate* rayPt = ray->getPosition();
    Vector* rayDir = ray->getDirection();

    Eigen::Vector4f returnPt(rayPt->getX(), rayPt->getY(), rayPt->getZ(), 1.0f);
    Eigen::Vector4f returnDir(rayDir->getX(), rayDir->getY(), rayDir->getZ(), 0.0f);

    Eigen::Matrix4f matrix = mat->getMatrix();

    returnPt = matrix * returnPt;
    returnDir = matrix * returnDir;

    Coordinate* newPt = new Coordinate(returnPt(0), returnPt(1), returnPt(2));
    Vector* newDir = new Vector(returnDir(0), returnDir(1), returnDir(2));

    return new Ray(newPt, newDir);
}

Ray* Transformation::rayToWorld(Ray* ray) {
    Coordinate* rayPt = ray->getPosition();
    Vector* rayDir = ray->getDirection();

    Eigen::Vector4f returnPt(rayPt->getX(), rayPt->getY(), rayPt->getZ(), 1.0f);
    Eigen::Vector4f returnDir(rayDir->getX(), rayDir->getY(), rayDir->getZ(), 0.0f);

    Eigen::Matrix<float,4,4> invMatrix = inverseMatrix->getMatrix();

    returnPt = invMatrix * returnPt;
    returnDir = invMatrix * returnDir;

    Coordinate* newPt = new Coordinate(returnPt(0), returnPt(1), returnPt(2));
    Vector* newDir = new Vector(returnDir(0), returnDir(1), returnDir(2));

    return new Ray(newPt, newDir);
}

Light* Transformation::lightToObject(Light* light) {
    Light* returnLight;
    Eigen::Matrix<float,4,4> matrix = mat->getMatrix();

    if(light->isPointLight()) {
        Coordinate* lightPos = light->getPosition();
        Eigen::Vector4f lightPt(lightPos->getX(), lightPos->getY(), lightPos->getZ(), 1.0f);

        lightPt = matrix * lightPt;

        returnLight = new PointLight(new Coordinate(lightPt(0),lightPt(1), lightPt(2)), light->getColor());
    } else {
        Vector* lightDir = light->getDirection();
        Eigen::Vector4f lightVec(lightDir->getX(), lightDir->getY(), lightDir->getZ(), 0.0f);

        lightVec = matrix * lightVec;

        returnLight = new PointLight(new Coordinate(lightVec(0),lightVec(1), lightVec(2)), light->getColor());
    }

    return returnLight;
}

Light* Transformation::lightToWorld(Light* light) {
    Light* returnLight;
    Eigen::Matrix<float,4,4> invMatrix = inverseMatrix->getMatrix();

    if(light->isPointLight()) {
        Coordinate* lightPos = light->getPosition();
        
        if(lightPos == NULL) {
            returnLight = NULL;
        } else {

            Eigen::Vector4f lightPt(lightPos->getX(), lightPos->getY(), lightPos->getZ(), 1.0f);
            lightPt = invMatrix * lightPt;

            returnLight = new PointLight(new Coordinate(lightPt(0),lightPt(1), lightPt(2)), light->getColor());
         }   
    } else {
        Vector* lightDir = light->getDirection();

        if(lightDir == NULL) {
            returnLight = NULL;
        } else {
        
            Eigen::Vector4f lightVec(lightDir->getX(), lightDir->getY(), lightDir->getZ(), 0.0f);

            lightVec = invMatrix * lightVec;

            returnLight = new PointLight(new Coordinate(lightVec(0),lightVec(1), lightVec(2)), light->getColor());
        }
    }

    return returnLight;
}

Vector* Transformation::vectorToObject(Vector* vec) {
  
    Eigen::Vector4f returnDir(vec->getX(), vec->getY(), vec->getZ(), 0.0f);
    Eigen::Matrix<float,4,4> matrix = mat->getMatrix();

    returnDir = matrix * returnDir;

    Vector* result = new Vector(returnDir(0), returnDir(1), returnDir(2));

    return result;
}

Vector* Transformation::vectorToWorld(Vector* vec) {
    Eigen::Vector4f returnDir(vec->getX(), vec->getY(), vec->getZ(), 0.0f);
    Eigen::Matrix<float,4,4> invMatrix = inverseMatrix->getMatrix();

    returnDir = invMatrix * returnDir;


    Vector* result = new Vector(returnDir(0), returnDir(1), returnDir(2));
    return result;
}

Vector* Transformation::normalToObject(Vector* vec) {
    std::cout << "This case should not be needed" << std::endl;
    return new Vector();
}

// Uses the inverse transpose matrix
Vector* Transformation::normalToWorld(Vector* vec) {
    Eigen::Vector4f normal(vec->getX(), vec->getY(), vec->getZ(), 0.0f);

    Eigen::Matrix<float,4,4> minv = inverseMatrix->getMatrix();
    Eigen::Matrix<float,4,4> minvTranspose = minv.transpose();

    normal = minvTranspose * normal;

    Vector* result = new Vector(normal(0), normal(1), normal(2));

    return result;
}




Coordinate* Transformation::transformPt(Coordinate* pt) {
    return mat->transformPt(pt);
}

Vector* Transformation::transformVec(Vector* vec) {
    return mat->transformVec(vec);
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

    Transformation* test = transform->getCopy();

    std::cout << "Testing if copying transformation can affect previous changes" << std::endl;

    transform->print();
    
    transform->rotate(0.0f, 0.0f, 1.0f, 30);
    test->print();
    


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
}

*/
