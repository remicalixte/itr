#include "libtime.h"

#ifndef Chrono_h_INCLUDED
#define Chrono_h_INCLUDED

class Chrono
{
private:
    timespec startTime_;
    timespec stopTime_;

public:
    Chrono(/* args */);
    ~Chrono();
    void stop();
    void restart();
    bool isActive();
    double startTime();
    double stopTime();
    double lap();
};

#endif