#include "PeriodicTimer.h"

#ifndef CountDown_H
#define CountDown_H

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
