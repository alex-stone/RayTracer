#include <iostream>
//#include "Sample.h"
#include "Sampler.h"

//using namespace std;

//****************************************************
// Sampler Class
//****************************************************

Sampler::Sampler() {
    setSampleSize(480, 640);
    currentSample = new Sample(0, 0);
}

Sampler::Sampler(int h, int w) {
    setSampleSize(h, w);
    currentSample = new Sample(0, 0);   
}

void Sampler::setSampleSize(int h, int w) {
    pixelHeight = h;
    pixelWidth = w;

}

Sample* Sampler::getSample(int x, int y) {
    return new Sample(x, y);
}

// Returns next sample in the horizontal line and changes line when
// it gets to the end

Sample* Sampler::getNextSample(Sample* samp) {

   int x = samp->getX();
   int y = samp->getY();
   if (x >= pixelWidth-1) {
        if(y >= pixelHeight - 1) {
            return NULL;
        } else {
            x = 0;
            y += 1;
        }
    } else {
        x += 1;
    }

//    samp->setSample(x,y);
    return new Sample(x,y);

}
/*
bool Sampler::getNextSample(Sample* samp) {
   if(samp->getX() == -1 && samp->getY() == -1) {
       samp = new Sample(0,0);
       return true;
   }

   int x = samp->getX();
   int y = samp->getY(); 
   if (x >= pixelWidth-1) {
        if(y >= pixelHeight - 1) {
	    return false;
        } else {
            x = 0;
	    y += 1;
 	}
    } else {
        x += 1;
    }


    std::cout << "X = " << x << ", Y = " << y << std::endl;
//    samp->setSample(x,y);
    samp = new Sample(x,y);
    return true;
}
*/
/*
int main(int argc, char* argv[]) {
    Sampler* test = new Sampler(4, 5);

    std::cout << "Testing Sampler with a window size of 5 x 4" << std::endl;

    Sample* temp = test->getSample(0,0);
   
    while(test->getNextSample(temp)) {
        temp->print();
    }

}
*/
