
#include "Sampler.h"

using namespace std;

//****************************************************
// Sampler Class
//****************************************************

Sampler::Sampler() {
    setSampleSize(480, 640);
    currentSample = new Sample(0, 0);
}

Sampler::Sampler(int h, int w) {
    setSampleSize(h, w);
    currentSample = newSample(0, 0);   
}

void Sampler::setSampleSize(int h, int w) {
    pixelHeight = h;
    pixelWidth = w;

}

Sample getSample(int x, int y) {
    return new Sample(x, y);
}

// Returns next sample in the horizontal line and changes line when
// it gets to the end
Sample getNextSample() {
   int x = currentSample.getX();
   int y = currentSample.getY(); 
   if (x >= pixelWidth-1) {
        if(y >= pixelHeight - 1) {
	    return null;
        } else {
            x = 0;
	    y += 1;
 	}
    } else {
        x += 1;
    }

    return getSample(x, y);
}
