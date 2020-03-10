#include "Chrono.h"

Chrono::Chrono() {
    restart();
}

Chrono::~Chrono() {
}

void Chrono::stop() {
    stopTime_ = timespec_now();
}

void Chrono::restart() {
    startTime_ = timespec_now();
    stopTime_ = timespec_from_ms(0);
}

bool Chrono::isActive() {
    return stopTime_ == timespec_from_ms(0);
}

double Chrono::startTime() {
    return timespec_to_ms(startTime_);
}

double Chrono::stopTime() {
    return timespec_to_ms(stopTime_);
}

double Chrono::lap() {
    timespec time = stopTime_;
    if (stopTime_ == timespec_from_ms(0)) {
        time = startTime_;
    }
    return timespec_to_ms(timespec_now() - time);
}