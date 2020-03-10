#include "Timer.h"

#ifndef PerdiodicTimer_H
#define PerdiodicTimer_H

class PeriodicTimer : public Timer {
   private:
    /* data */
   public:
    void start(double duration_ms);
};

#endif