#include <exception>

#include "libtime.h"
#include "pthread.h"

#ifndef Mutex_h_INCLUDED
#define Mutex_h_INCLUDED

class Mutex
{
public:
    class Monitor
    {
    public:
        class TimeoutException : public std::exception
        {
        };

        void wait();
        bool wait(double timeout_ms);
        void notify();
        void notifyAll();

    protected:
        Monitor(Mutex &m);
        Mutex &mutex;
    };
    class Lock : public Mutex::Monitor
    {
    public:
        Lock(Mutex &m);
        Lock(Mutex &m, double timeout_ms);
        ~Lock();
    };
    class TryLock : public Mutex::Monitor
    {
        TryLock(Mutex &m);
        ~TryLock();
    };

    Mutex();
    ~Mutex();

private:
    pthread_mutex_t posixId;
    pthread_cond_t posixCondId;

    void lock();
    bool lock(double timeout_ms);
    bool trylock();
    void unlock();
};

#endif