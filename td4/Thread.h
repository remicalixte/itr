#include <unistd.h>

#include "PosixThread.h"

class Thread : public PosixThread {
   private:
    timespec startTime;
    timespec stopTime;

   public:
    Thread(/* args */);
    ~Thread();
    void start();
    virtual void run();
    static void* call_run(void* v_thread);
    static void sleep_ms(double delay_ms);
    double startTime_ms();
    double stopTime_ms();
    double execTime_ms();
};
