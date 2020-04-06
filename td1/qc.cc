#include <signal.h>
#include <stdio.h>

#include <iostream>

#include "libtime.h"

using namespace std;

unsigned incr(unsigned int nLoops, double* pCounter) {
    size_t i;
    for (i = 0; i < nLoops; i++) {
        (*pCounter)++;
    }

    return i;
}

int main(int argc, char const* argv[]) {
    if (argc < 2) {
        printf("needs a counter argument\n");
        return 1;
    }
    unsigned int nLoops = stol(argv[1]);
    double counter = 0;

    timespec before = timespec_now();
    incr(nLoops, &counter);
    timespec after = timespec_now();

    timespec duration = after - before;

    printf("%f in %f seconds\n", counter, timespec_to_ms(duration) / 1000);

    return 0;
}