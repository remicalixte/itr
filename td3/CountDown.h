#include "PeriodicTimer.h"

#ifndef CountDown_h_INCLUDED
#define CountDown_h_INCLUDED

class CountDown : public PeriodicTimer {
   private:
    int n;

   public:
    int getn();
    CountDown(int n);
    ~CountDown();
    virtual void callback();
};

#endif
