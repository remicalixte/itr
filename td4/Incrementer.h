#include "Mutex.h"
#include "Thread.h"

#ifndef Incrementer_h_INCLUDED
#define Incrementer_h_INCLUDED

class Incrementer : public Thread {
   private:
    volatile double *pCounter;
    int n;
    bool protect;
    Mutex *mu;

   public:
    Incrementer(volatile double *pCounter, int n, bool protect = false, Mutex *mu = nullptr);
    ~Incrementer();

   protected:
    virtual void run();
};

#endif