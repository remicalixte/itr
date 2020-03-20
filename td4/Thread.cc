#include "Thread.h"

#include <iostream>

Thread::Thread(/* args */) : PosixThread() {
    startTime = timespec_from_ms(0);
    stopTime = timespec_from_ms(0);
}

Thread::~Thread() {
}

void Thread::start() {
    PosixThread::start(call_run, this);
    startTime = timespec_now();
}

void Thread::run() {
    std::cout << "base run called\n";
}

void* Thread::call_run(void* v_thread) {
    std::cout << "in call_run " << v_thread << std::endl;
    auto thread = (Thread*)v_thread;
    std::cout << "cast to thread\n";
    thread->run();

    thread->stopTime = timespec_now();

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