#include "Calibrator.h"
#include "CpuLoop.h"

int main() {
    auto calibrator = Calibrator(2000, 3);

    double duration_ms = 2000;
    auto loop = CpuLoop(&calibrator);
    auto start = timespec_now();
    loop.runTime(duration_ms);
    auto end = timespec_now();

    printf("expected time: %lf ms, got : %lf ms\n", duration_ms, timespec_to_ms(end - start));

    return 0;
}
