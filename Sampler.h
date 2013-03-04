#ifndef SAMPLER_H
#define SAMPLER_H

#include <iostream>
#include "Sample.h"

//****************************************************
// Sampler Header Definition
//****************************************************

class Sampler {
  private:
    int pixelHeight;
    int pixelWidth;
    Sample* currentSample;

  public:
    Sampler();
    Sampler(int h, int w);

    void setSampleSize(int h, int w);
    bool getNextSample(Sample* samp);
    Sample* getSample(int x, int y);

};

#endif
