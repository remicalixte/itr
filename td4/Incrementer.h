#include "Thread.h"

class Incrementer : public Thread {
   private:
    volatile double *pCounter;
    int n;

   public:
    Incrementer(volatile double *pCounter, int n);
    ~Incrementer();
    virtual void run();
};
