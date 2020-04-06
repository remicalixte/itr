#include <stdlib.h>

#include <vector>

#include "Incrementer.h"

using namespace std;
int main() {
    volatile double counter = 0;
    int n = 20;
    auto incr = Incrementer(&counter, n);
    incr.start();
    auto incr2 = Incrementer(&counter, n);
    incr2.start();

    sleep(3);
    std::cout << "count value: " << counter << std::endl;
}