#include <signal.h>
#include <stdio.h>

#include "libtime.h"

#ifndef Timer_h_INCLUDED
#define Timer_h_INCLUDED

class Timer {
   private:
    sigevent sev;
    void static call_callback(int, siginfo_t *si, void *);

   public:
    Timer(/* args */);
    ~Timer();
    void start(double duration_ms);
    void stop();

   protected:
    timer_t tid;
    virtual void callback() = 0;
};

#endif