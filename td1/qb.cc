#include <signal.h>
#include <stdio.h>

#include "libtime.h"

using namespace std;

void setup_timer();
void timer_handler(int sig, siginfo_t *si, void *);

void timer_handler(int, siginfo_t *si, void *)
{
    int *counter = (int *)si->si_value.sival_ptr;

    printf("%d\n", *counter);
    (*counter)++;
}

void setup_timer(double time_ms, void (*callback)(int, siginfo_t *si, void *))
{
    struct sigaction sa;
    sa.sa_flags = SA_SIGINFO;
    sa.sa_sigaction = callback;
    sigemptyset(&sa.sa_mask);
    sigaction(SIGRTMIN, &sa, nullptr);

    volatile int counter = 0;
    struct sigevent sev;
    sev.sigev_notify = SIGEV_SIGNAL;
    sev.sigev_signo = SIGRTMIN;
    sev.sigev_value.sival_ptr = (void *)&counter;

    timer_t tid;
    timer_create(CLOCK_REALTIME, &sev, &tid);
    itimerspec its;
    its.it_value = timespec_from_ms(time_ms);
    its.it_interval = timespec_from_ms(time_ms);

    timer_settime(tid, 0, &its, nullptr);

    while (counter < 15)
    {
    }

    itimerspec its2;
    its2.it_value = timespec_from_ms(0);
    its2.it_interval = timespec_from_ms(0);
    timer_settime(tid, 0, &its2, nullptr);
    timer_delete(tid);
}

int main()
{
    setup_timer(500, timer_handler);
    return 0;
}