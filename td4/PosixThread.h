#include <exception>

#include "errno.h"
#include "libtime.h"
#include "pthread.h"

#ifndef PosixThread_h_INCLUDED
#define PosixThread_h_INCLUDED

class PosixThread {
   private:
    pthread_t posixId;
    pthread_attr_t posixAttr;
    bool isActive;

   public:
    class Exception : public std::exception {
    };

    PosixThread();
    PosixThread(pthread_t posixId);
    ~PosixThread();
    void start(void *(*threadFunc)(void *), void *threadArg);
    void join();
    bool join(double timeout_ms);
    bool setScheduling(int schedPolicy, int priority);
    bool getScheduling(int *p_schedPolicy, int *p_priority);
};

#endif