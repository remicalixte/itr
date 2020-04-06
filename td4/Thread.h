#include <unistd.h>

#include "Mutex.h"
#include "PosixThread.h"

#ifndef Thread_h_INCLUDED
#define Thread_h_INCLUDED

class Thread : public PosixThread {
   private:
    timespec startTime;
    timespec stopTime;
    bool started = false;
    Mutex startedMu;

   public:
    Thread(/* args */);
    ~Thread();
    bool start();
    virtual void run() = 0;
    static void* call_run(void* v_thread);
    static void sleep_ms(double delay_ms);
    double startTime_ms();
    double stopTime_ms();
    double execTime_ms();
};

#endif