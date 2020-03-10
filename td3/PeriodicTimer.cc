#include "PeriodicTimer.h"

void PeriodicTimer::start(double duration_ms) {
    itimerspec its = {
        it_interval : timespec_from_ms(duration_ms),
        it_value : timespec_from_ms(duration_ms),
    };

    timer_settime(tid, 0, &its, nullptr);
}
