#include "Thread.h"

#include <iostream>

Thread::Thread(/* args */) : PosixThread() {
    startTime = timespec_from_ms(0);
    stopTime = timespec_from_ms(0);
}

Thread::~Thread() {
}

bool Thread::start() {
    auto lock = Mutex::Lock(startedMu);
    if (started) {
        return false;
    }
    startTime = timespec_now();
    PosixThread::start(call_run, this);
    return true;
}

void* Thread::call_run(void* v_thread) {
    auto thread = (Thread*)v_thread;
    thread->run();

    thread->stopTime = timespec_now();
    auto lock = Mutex::Lock(thread->startedMu);
    thread->started = false;

    return nullptr;
}

void Thread::sleep_ms(double delay_ms) {
    usleep(delay_ms * 1000);
}

double Thread::startTime_ms() {
    return timespec_to_ms(startTime);
}
double Thread::stopTime_ms() {
    return timespec_to_ms(stopTime);
}

double Thread::execTime_ms() {
    return timespec_to_ms(timespec_now() - startTime);
}