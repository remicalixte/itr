#include "Semaphore.h"

#ifndef Request_h_INCLUDED
#define Request_h_INCLUDED

class Request
{
private:
public:
    Request(/* args */);
    ~Request();
    virtual void execute() = 0;
    void waitReturn();

protected:
    Semaphore returnSema;
};

#endif