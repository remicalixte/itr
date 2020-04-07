#include "Incrementer.h"

#include <iostream>
Incrementer::Incrementer(volatile double* pCounter, int n, bool protect, Mutex* mu) : pCounter(pCounter), n(n), protect(protect), mu(mu) {
}

Incrementer::~Incrementer() {
}

void Incrementer::run() {
    if (protect) {
        {
            auto lock = Mutex::Lock(*mu);
            for (int i = 0; i < n; i++) {
                (*pCounter)++;
            }
        }
    } else {
        for (int i = 0; i < n; i++) {
            (*pCounter)++;
        }
    }
}
