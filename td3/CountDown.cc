#include "CountDown.h"

CountDown::CountDown(int n) : n(n) {
}

CountDown::~CountDown(){};

void CountDown::callback() {
    this->n--;
    if (n == 0) {
        stop();
    }
}

int CountDown::getn() {
    return n;
}