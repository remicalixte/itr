#include "Producer.h"

Producer::Producer(Semaphore& sema) : sema(sema) {
}

Producer::~Producer() {
}

void Producer::run() {
    sema.give();
}