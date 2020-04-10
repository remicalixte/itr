#include "Fifo.hh"
#include "Mutex.h"
#include "Thread.h"

class FifoConsumer : public Thread
{
private:
    Fifo<int> *fifo;
    Mutex *mu;
    volatile unsigned *counter;
    bool stop_ = false;

public:
    FifoConsumer(Fifo<int> *fifo, Mutex *mu, volatile unsigned *counter);
    ~FifoConsumer();
    virtual void run();
    void stop();
};
