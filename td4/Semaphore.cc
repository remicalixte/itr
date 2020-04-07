#include "Semaphore.h"

#include <stdio.h>

Semaphore::Semaphore(unsigned iniCount, unsigned maxCount) : counter(iniCount), maxCount(maxCount) {
}

Semaphore::~Semaphore(){};

void Semaphore::give() {
    auto lock = Mutex::Lock(mutex);
    if (counter < maxCount) {
        counter++;
    }
    if (counter == 1) {
        // wakes any thread that whould be listening
        Mutex::Monitor(mutex).notifyAll();
    }
}

void Semaphore::take() {
    {
        auto lock = Mutex::Lock(mutex);
        if (counter > 0) {
            counter--;
            return;
        }

        // counter is 0
        Mutex::Monitor(mutex).wait();
    }
    // we can retry
    take();
}

bool Semaphore::take(double timeout_ms) {
    auto start = timespec_now();
    {
        auto lock = Mutex::Lock(mutex);
        if (counter > 0) {
            counter--;
            return true;
        }

        // counter is 0
        if (!Mutex::Monitor(mutex).wait(timeout_ms)) {
            return false;
        }
    }

    auto end = timespec_now();
    auto elapsed = end - start;

    // we can retry with the remaining time
    return take(timeout_ms - timespec_to_ms(elapsed));
}

unsigned Semaphore::getCounter() {
    return counter;
}