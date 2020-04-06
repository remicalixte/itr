#include <float.h>

#ifndef Looper_h_INCLUDED
#define Looper_h_INCLUDED

class Looper {
   private:
    volatile bool doStop = false;
    double iLoop;

   public:
    Looper(/* args */);
    ~Looper();
    double runLoop(double nLoops = DBL_MAX);
    double getSample();
    double stopLoop();
};

#endif