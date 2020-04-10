#include "Calibrator.h"

Calibrator::Calibrator(double samplingPeriod_ms, unsigned nSamples) : nSamples(nSamples)
{
    start(samplingPeriod_ms);
    looper.runLoop();
    stop();

    // min squared regression
    double average_t = 0;
    for (unsigned i = 0; i < nSamples; i++)
    {
        average_t += samplingPeriod_ms * (i + 1);
    }
    average_t /= nSamples;

    double average_l = 0;
    for (auto it = samples.begin(); it != samples.end(); it++)
    {
        average_l += *it;
    }
    average_l /= nSamples;

    double an = 0;
    for (unsigned i = 0; i < nSamples; i++)
    {
        an += (samples[i] - average_l) * (samplingPeriod_ms * (i + 1) - average_t);
    }
    double ad = 0;
    for (unsigned i = 0; i < nSamples; i++)
    {
        ad += (samplingPeriod_ms * (i + 1) - average_t) * (samplingPeriod_ms * (i + 1) - average_t);
    }

    a = an / ad;

    b = samples[0] - a * samplingPeriod_ms;
}

Calibrator::~Calibrator()
{
}

void Calibrator::callback()
{
    if (nSamples <= 1)
    {
        samples.push_back(looper.stopLoop());
    }
    else
    {
        samples.push_back(looper.getSample());
    }
    nSamples--;
}

double Calibrator::nLoops(double duration_ms)
{
    return a * duration_ms + b;
}