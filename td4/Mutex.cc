#include "Mutex.h"

Mutex::Mutex()
{
    pthread_mutexattr_t attr;
    pthread_mutexattr_init(&attr);
    pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);

    pthread_mutex_init(&posixId, &attr);
    pthread_cond_init(&posixCondId, nullptr);

    pthread_mutexattr_destroy(&attr);
}

Mutex::~Mutex()
{
    pthread_mutex_destroy(&posixId);
    pthread_cond_destroy(&posixCondId);
}

void Mutex::lock()
{
    pthread_mutex_lock(&posixId);
}

bool Mutex::lock(double timeout_ms)
{
    auto deadline = timespec_now() + timespec_from_ms(timeout_ms);
    return pthread_mutex_timedlock(&posixId, &deadline) == 0;
}

bool Mutex::trylock()
{
    return pthread_mutex_trylock(&posixId) == 0;
}

void Mutex::unlock()
{
    pthread_mutex_unlock(&posixId);
}

Mutex::Monitor::Monitor(Mutex &m) : mutex(m) {}

void Mutex::Monitor::wait()
{
    pthread_cond_wait(&mutex.posixCondId, &mutex.posixId);
}

bool Mutex::Monitor::wait(double timeout_ms)
{
    auto deadline = timespec_now() + timespec_from_ms(timeout_ms);

    return pthread_cond_timedwait(&mutex.posixCondId, &mutex.posixId, &deadline) == 0;
}

void Mutex::Monitor::notify()
{
    pthread_cond_signal(&mutex.posixCondId);
}

void Mutex::Monitor::notifyAll()
{
    pthread_cond_broadcast(&mutex.posixCondId);
}

Mutex::Lock::Lock(Mutex &m) : Mutex::Monitor(m)
{
    mutex.lock();
}

Mutex::Lock::Lock(Mutex &m, double timeout_ms) : Mutex::Monitor(m)
{
    if (!mutex.lock(timeout_ms))
    {
        throw Mutex::Monitor::TimeoutException();
    }
}

Mutex::Lock::~Lock()
{
    mutex.unlock();
}

Mutex::TryLock::TryLock(Mutex &m) : Mutex::Monitor(m)
{
    if (!mutex.trylock())
    {
        throw Mutex::Monitor::TimeoutException();
    }
}

Mutex::TryLock::~TryLock()
{
    mutex.unlock();
}
