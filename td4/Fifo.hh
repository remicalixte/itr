#include <stdio.h>

#include <exception>
#include <queue>

#include "Mutex.h"

#ifndef Fifo_h_INCLUDED
#define Fifo_h_INCLUDED

template <class T>
class Fifo {
   private:
    std::queue<T> elements;
    class EmptyException : public std::exception {};
    Mutex mutex;

   public:
    void push(T element);
    T pop();
    T pop(double timeout_ms);
};

template <class T>
void Fifo<T>::push(T element) {
    auto lock = Mutex::Lock(mutex);
    elements.push(element);
    lock.notifyAll();
}

template <class T>
T Fifo<T>::pop() {
    auto lock = Mutex::Lock(mutex);
    while (elements.empty()) {
        lock.wait();
    }

    auto element = elements.front();
    elements.pop();

    return element;
}

template <class T>
T Fifo<T>::pop(double timeout_ms) {
    auto start = timespec_now();

    auto lock = Mutex::Lock(mutex);
    while (timeout_ms > 0 && elements.empty()) {
        if (!lock.wait(timeout_ms)) {
            return T{};
        }

        //update timeout_ms
        auto now = timespec_now();
        auto elapsed = now - start;
        timeout_ms -= timespec_to_ms(elapsed);

        //update start if we need to wait again
        start = now;
    }
    auto element = elements.front();
    elements.pop();

    return element;
}

#endif