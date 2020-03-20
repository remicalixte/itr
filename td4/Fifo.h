#include <exception>
#include <queue>

#include "Mutex.h"

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
