#include <exception>
#include <iostream>

#include "libtime.h"
#include "pthread.h"

class Mutex {
   public:
    class Monitor {
       public:
        class TimeoutException : public std::exception {};

        Monitor(Mutex &m);
        void wait();
        bool wait(double timeout_ms);
        void notify();
        void notifyAll();

       protected:
        Mutex &mutex;
    };
    class Lock : public Mutex::Monitor {
       public:
        Lock(Mutex &m);
        Lock(Mutex &m, double timeout_ms);
        ~Lock();
    };
    class TryLock : public Mutex::Monitor {
        TryLock(Mutex &m);
        ~TryLock();
    };

    Mutex();
    ~Mutex();

   protected:
    pthread_mutex_t posixId;
    pthread_cond_t posixCondId;

    void lock();
    bool lock(double timeout_ms);
    bool trylock();
    void unlock();
};
