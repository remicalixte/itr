#include "timer.h"

#include <assert.h>
#include <limits.h>
#include <signal.h>
#include <stdio.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

#include <iostream>
#include <string>

#include "libtime.h"

using namespace std;

void timer_handler(int, siginfo_t* si, void*) {
    int* counter = (int*)si->si_value.sival_ptr;

    printf("%d\n", *counter);
    (*counter)++;
}

void setup_timer(double time_ms, void (*callback)(int, siginfo_t* si, void*)) {
    struct sigaction sa;
    sa.sa_flags = SA_SIGINFO;
    sa.sa_sigaction = callback;
    sigemptyset(&sa.sa_mask);
    sigaction(SIGRTMIN, &sa, nullptr);

    volatile int counter = 0;
    struct sigevent sev;
    sev.sigev_notify = SIGEV_SIGNAL;
    sev.sigev_signo = SIGRTMIN;
    sev.sigev_value.sival_ptr = (void*)&counter;

    timer_t tid;
    timer_create(CLOCK_REALTIME, &sev, &tid);
    itimerspec its;
    its.it_value = timespec_from_ms(time_ms);
    its.it_interval = timespec_from_ms(time_ms);

    timer_settime(tid, 0, &its, nullptr);

    while (counter < 15) {
    }

    itimerspec its2;
    its2.it_value = timespec_from_ms(0);
    its2.it_interval = timespec_from_ms(0);
    timer_settime(tid, 0, &its2, nullptr);
    timer_delete(tid);
}

unsigned incr(unsigned int nLoops, double* pCounter, volatile bool* pStop) {
    size_t i;
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

int main() {
    // timespec now = timespec_now();
    // timespec now2 = timespec_from_ms(timespec_to_ms(now));
    // assert(now - now2 < timespec_from_ms(0.0001) || now2 - now < timespec_from_ms(0.0001));

    // sleep(1);
    // timespec after = timespec_now();
    // assert(now - after < timespec_from_ms(0));
    // assert(after - now > timespec_from_ms(0));
    // assert(after - after == timespec_from_ms(0));
    // assert(after != now);

    // setup_timer(500, time_handler);

    // if (argc < 2) {
    //     printf("needs a counter argument\n");
    //     return 1;
    // }
    //unsigned int nLoops = stol(argv[1]);
    unsigned int nLoops = UINT_MAX;
    double counter = 0;
    volatile bool stop = false;
    int ret;

    struct sigaction sa;
    sa.sa_flags = SA_SIGINFO;
    sa.sa_sigaction = incr_stop;
    ret = sigemptyset(&sa.sa_mask);
    if (ret != 0) {
        printf("sigemptyset\n");
        return 1;
    }
    ret = sigaction(SIGRTMIN, &sa, nullptr);

    struct sigevent sev;
    sev.sigev_notify = SIGEV_SIGNAL;
    sev.sigev_signo = SIGRTMIN;
    sev.sigev_value.sival_ptr = (void*)&stop;

    timer_t tid;
    ret = timer_create(CLOCK_REALTIME, &sev, &tid);
    if (ret != 0) {
        printf("timer_create\n");
        return 1;
    }
    itimerspec its;
    its.it_value = timespec_from_ms(1000);
    its.it_interval = timespec_from_ms(0);
    printf("%ld %ld\n", its.it_value.tv_sec, its.it_value.tv_nsec);
    ret = timer_settime(tid, 0, &its, nullptr);
    if (ret != 0) {
        printf("timer_settime\n");
        return 1;
    }

    timespec before = timespec_now();
    incr(nLoops, &counter, &stop);
    timespec after = timespec_now();

    timespec duration = after - before;

    printf("%f in %f seconds\n", counter, timespec_to_ms(duration) / 1000);

    return 0;
}