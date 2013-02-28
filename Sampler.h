#include <iostream>

class Sampler {
  private:
    int pixelHeight;
    int pixelWidth;
    Sample currentSample;

  public:
    Sampler();
    Sampler(int h, int w);

    void setSampleSize(int h, int w);
    Sample getNextSample();
    Sample getSample(int x, int y);

}
