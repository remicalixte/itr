#include "Timer.h"

#ifndef PerdiodicTimer_h_INCLUDED
#define PerdiodicTimer_h_INCLUDED

class PeriodicTimer : public Timer
{
private:
    /* data */
public:
    void start(double duration_ms);
};

#endif