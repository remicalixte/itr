#include "Fifo.hh"
#include "Request.h"
#include "Thread.h"

#ifndef ActiveObject_h_INCLUDED
#define ActiveObject_h_INCLUDED

class ActiveObject : public Thread
{
private:
    bool stopped = false;

public:
    ActiveObject(/* args */);
    ~ActiveObject();
    virtual void run();
    void stop();

protected:
    Fifo<Request *> reqFifo;
};

#endif