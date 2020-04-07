#include "Mutex.h"
#include "libtime.h"
#include "limits.h"

#ifndef Semaphore_h_INCLUDED
#define Semaphore_h_INCLUDED
class Semaphore {
   private:
    unsigned counter;
    unsigned maxCount;
    Mutex mutex;

   public:
    Semaphore(unsigned iniCount = 0, unsigned maxCount = UINT_MAX);
    ~Semaphore();
    void give();
    void take();
    bool take(double timeout_ms);
    unsigned getCounter();
};

#endif