#include "CpuLoop.h"

CpuLoop::CpuLoop(Calibrator *calibrator) : calibrator(calibrator)
{
}

CpuLoop::~CpuLoop()
{
}

void CpuLoop::runTime(double duration_ms)
{
    double nLoops = calibrator->nLoops(duration_ms);
    runLoop(nLoops);
}