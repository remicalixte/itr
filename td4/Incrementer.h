#include "Thread.h"

#ifndef Incrementer_h_INCLUDED
#define Incrementer_h_INCLUDED

class Incrementer : public Thread {
   private:
    volatile double *pCounter;
    int n;

   public:
    Incrementer(volatile double *pCounter, int n);
    ~Incrementer();
    virtual void run();
};

#endif