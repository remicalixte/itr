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
    Mutex::Monitor(mutex).notify();
}

template <class T>
T Fifo<T>::pop() {
    {
        auto lock = Mutex::Lock(mutex);
        if (!elements.empty()) {
            auto element = elements.front();
            elements.pop();

            return element;
        }

        printf("is empty\n");
        // elements is empty
        Mutex::Monitor(mutex).wait();
        printf("wait finished\n");
    }
    return pop();
}

template <class T>
T Fifo<T>::pop(double timeout_ms) {
    auto start = timespec_now();
    {
        auto lock = Mutex::Lock(mutex);
        if (!elements.empty()) {
            auto element = elements.front();
            elements.pop();

            return element;
        }

        // elements is empty
        if (!Mutex::Monitor(mutex).wait(timeout_ms)) {
            return false;
        }
    }

    auto end = timespec_now();
    auto elapsed = end - start;

    // we can retry with the remaining time
    return pop(timeout_ms - timespec_to_ms(elapsed));
}

#endif