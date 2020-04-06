#include <limits.h>
#include <signal.h>
#include <stdio.h>
#include <time.h>

#include <iostream>
#include <string>

#include "errno.h"
#include "libtime.h"
#include "timer.h"

using namespace std;

unsigned long incr(unsigned long nLoops, double* pCounter, volatile bool* pStop);
void incr_stop(int, siginfo_t* si, void*);
int setup_timer(timer_t* tid, itimerspec* its, sigevent* sev, double duration_ms, volatile bool* pStop);
int calib();

int setup_timer(timer_t* tid, itimerspec* its, sigevent* sev, double duration_ms, volatile bool* pStop) {
    struct sigaction sa;
    sa.sa_flags = SA_SIGINFO;
    sa.sa_sigaction = incr_stop;
    int ret = sigemptyset(&sa.sa_mask);
    if (ret != 0) {
        printf("sigemptyset\n");
        return 1;
    }
    ret = sigaction(SIGRTMIN, &sa, nullptr);

    sev->sigev_notify = SIGEV_SIGNAL;
    sev->sigev_signo = SIGRTMIN;
    sev->sigev_value.sival_ptr = (void*)pStop;

    ret = timer_create(CLOCK_REALTIME, sev, tid);
    if (ret != 0) {
        printf("timer_create\n");
        return 1;
    }
    its->it_value = timespec_from_ms(duration_ms);
    its->it_interval = timespec_from_ms(0);
    ret = timer_settime(*tid, 0, its, nullptr);
    if (ret != 0) {
        printf("timer_settime: %d\n", errno);
        return 1;
    }

    return 0;
}

unsigned long incr(unsigned long nLoops, double* pCounter, volatile bool* pStop) {
    unsigned long i;
    for (i = 0; !(*pStop) && i < nLoops; i++) {
        (*pCounter)++;
    }

    return i;
}

void incr_stop(int, siginfo_t* si, void*) {
    std::cout << "incr should stop" << std::endl;

    volatile bool* pStop = (volatile bool*)si->si_value.sival_ptr;
    *pStop = true;
}

int calib() {
    unsigned long nLoops = ULONG_MAX;
    double counter = 0;
    volatile bool stop = false;

    timer_t tid;
    itimerspec its;
    sigevent sev;
    setup_timer(&tid, &its, &sev, 4000, &stop);

    timespec before = timespec_now();
    double l1 = incr(nLoops, &counter, &stop);
    timespec after = timespec_now();
    double t1 = timespec_to_ms(after - before);
    printf("%f in %f seconds\n", counter, t1 / 1000);

    timer_delete(tid);
    counter = 0;
    stop = false;

    setup_timer(&tid, &its, &sev, 6000, &stop);
    before = timespec_now();
    double l2 = incr(nLoops, &counter, &stop);
    after = timespec_now();
    double t2 = timespec_to_ms(after - before);
    printf("%f in %f seconds\n", counter, t2 / 1000);

    timer_delete(tid);

    double a = (l2 - l1) / (t2 - t1);
    double b = l2 - a * t2;

    printf("calibration: a=%lf ms-1, b=%lf\n", a, b);

    return 0;
}

int main() {
    unsigned long nLoops = ULONG_MAX;
    double counter = 0;
    volatile bool stop = false;

    timer_t tid;
    itimerspec its;
    sigevent sev;
    setup_timer(&tid, &its, &sev, 4000, &stop);

    timespec before = timespec_now();
    incr(nLoops, &counter, &stop);
    timespec after = timespec_now();

    timespec duration = after - before;

    printf("%f in %f seconds\n", counter, timespec_to_ms(duration) / 1000);

    calib();

    return 0;
}