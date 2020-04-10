#include <stdio.h>

#include <vector>

#include "Looper.h"
#include "PeriodicTimer.h"

#ifndef Calibrator_h_INCLUDED
#define Calibrator_h_INCLUDED

class Calibrator : public PeriodicTimer
{
private:
    double a;
    double b;
    unsigned nSamples;
    std::vector<double> samples;
    Looper looper;

public:
    Calibrator(double samplingPeriod_ms, unsigned nSamples);
    ~Calibrator();
    double nLoops(double duration_ms);

protected:
    virtual void callback();
};

#endif