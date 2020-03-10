#include "CountDown.h"
#include "iostream"

int main(void) {
    CountDown countDown = CountDown(10);
    countDown.start(1000);

    int lastValue = 10;
    while (countDown.getn() > 0) {
        if (lastValue != countDown.getn()) {
            lastValue = countDown.getn();
            std::cout << lastValue << std::endl;
        }
    }

    return 0;
}
