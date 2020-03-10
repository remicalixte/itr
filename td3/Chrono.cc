#include "Chrono.h"

Chrono::Chrono() {
    startTime_ = timespec_now();
}

Chrono::~Chrono() {
}

void Chrono::stop() {
    stopTime_ = timespec_now();
    isActive_ = false;
}

void Chrono::restart() {
    startTime_ = timespec_now();
    isActive_ = true;
}

bool Chrono::isActive() {
    return isActive_;
}

double Chrono::startTime() {
    return timespec_to_ms(startTime_);
}

double Chrono::stopTime() {
    return timespec_to_ms(stopTime_);
}

double Chrono::lap() {
    timespec time = stopTime_;
    if (isActive_) {
        time = startTime_;
    }
    return timespec_to_ms(timespec_now() - time);
}