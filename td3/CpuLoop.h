#include "Calibrator.h"
#include "Looper.h"

#ifndef CpuLoop_h_INCLUDED
#define CpuLoop_h_INCLUDED

class CpuLoop : public Looper {
   private:
    Calibrator* calibrator;

   public:
    CpuLoop(Calibrator* calibrator);
    ~CpuLoop();
    void runTime(double duration_ms);
};

#endif