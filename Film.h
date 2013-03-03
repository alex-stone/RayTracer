#include <iostream>
#include "Color.h"
#include "Sample.h"

class Film {
  private:
    int pixelHeight;
    int pixelWidth;
    Color[][] pixelBucket;

  public:
    Film();
    Film(int h, int w);
    
    void setSize(int h, int w);
  
    void commit(Sample samp, Color color); 
    void writeImage();

};
