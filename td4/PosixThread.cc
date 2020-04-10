#include "PosixThread.h"

PosixThread::PosixThread()
{
    pthread_attr_init(&posixAttr);
    isActive = false;
}

PosixThread::PosixThread(pthread_t posixId)
{
    pthread_attr_init(&posixAttr);
    isActive = true;
    int policy;
    sched_param param;
    int retval = pthread_getschedparam(posixId, &policy, &param);
    if (retval == ESRCH)
    {
        // posixId is not running
        throw PosixThread::Exception();
    }

    pthread_attr_setschedpolicy(&posixAttr, policy);
    pthread_attr_setschedparam(&posixAttr, &param);
}

PosixThread::~PosixThread()
{
    pthread_attr_destroy(&posixAttr);
}

void PosixThread::start(void *(*threadFunc)(void *), void *threadArg)
{
    pthread_create(&posixId, &posixAttr, threadFunc, threadArg);
}

void PosixThread::join()
{
    pthread_join(posixId, nullptr);
}

bool PosixThread::join(double timeout_ms)
{
    timespec timeout = timespec_from_ms(timeout_ms);
    int retval = pthread_timedjoin_np(posixId, nullptr, &timeout);
    return retval == 0;
}

bool PosixThread::setScheduling(int schedPolicy, int priority)
{
    sched_param param = {
        sched_priority : priority,
    };
    int retval = pthread_setschedparam(posixId, schedPolicy, &param);
    if (retval != ESRCH)
    {
        return true;
    }
    // thread is not yet running, change the attr instead
    pthread_attr_setschedparam(&posixAttr, &param);
    pthread_attr_setschedpolicy(&posixAttr, schedPolicy);
    return true;
}

bool PosixThread::getScheduling(int *p_schedPolicy, int *p_priority)
{
    sched_param param;
    int retval = pthread_getschedparam(posixId, p_schedPolicy, &param);
    if (retval != ESRCH)
    {
        *p_priority = param.sched_priority;
        return true;
    }
    // thread is not yet running, return from attr instead
    pthread_attr_getschedparam(&posixAttr, &param);
    *p_priority = param.sched_priority;
    pthread_attr_getschedpolicy(&posixAttr, p_schedPolicy);

    return false;
}