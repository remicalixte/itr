#include <signal.h>

void setup_timer();
void timer_handler(int sig, siginfo_t* si, void*);

unsigned incr(unsigned int nLoops, double* pCounter, volatile bool* pStop);