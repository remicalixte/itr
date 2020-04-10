#include <assert.h>
#include <stdio.h>
#include <unistd.h>

#include "Chrono.h"

int main()
{
    auto chrono = Chrono();
    printf("%lf ms\n", chrono.lap());
    sleep(3);
    printf("%lf ms\n", chrono.lap());
    chrono.stop();
    printf("%lf ms\n", chrono.stopTime() - chrono.startTime());
    assert(!chrono.isActive());
    chrono.restart();
    assert(chrono.isActive());

    return 0;
}
