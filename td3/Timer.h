#include "libtime.h"
#include "signal.h"
#include "time.h"

#ifndef Timer_h_INCLUDED
#define Timer_h_INCLUDED

class Timer {
   private:
    sigevent sev;

   public:
    Timer(/* args */);
    ~Timer();
    void start(double duration_ms);
    void stop();
    virtual void callback() = 0;
    void static call_callback(int, siginfo_t *si, void *);

   protected:
    timer_t tid;
};

#endif