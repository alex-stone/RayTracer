#ifndef SAMPLE_H
#define SAMPLE_H

//****************************************************
// Sample Header Definition
//****************************************************

class Sample {
  private:
    int x, y;

  public:
    Sample();
    Sample(int a, int b);
    
    int getX() {return x; };
    int getY() {return y; };

    void setSample(int a, int b);
    void print();

    // No Set Functions, because a Sample's don't change coordinates
};

#endif
