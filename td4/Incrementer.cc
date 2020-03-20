#include "Incrementer.h"

#include <iostream>
Incrementer::Incrementer(volatile double *pCounter, int n) : pCounter(pCounter), n(n) {
}

Incrementer::~Incrementer() {
}

void Incrementer::run() {
    for (int i = 0; i < n; i++) {
        (*pCounter)++;
    }
}
