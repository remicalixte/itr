#include "ActiveCalc.h"
#include "stdio.h"

int main() {
    ActiveCalc acalc;
    printf("async calc to be started\n");
    acalc.start();
    printf("async calc started\n");

    CrunchReq* req = acalc.async_crunch(12);
    printf("sent async crunch\n");
    double result = req->waitReturn();

    printf("result: %lf\n", result);
    acalc.stop();

    return 0;
}
