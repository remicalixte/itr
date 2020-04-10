#include "Fifo.hh"
#include "Thread.h"

class FifoProducer : public Thread
{
private:
    Fifo<int> *fifo;
    unsigned n;

public:
    FifoProducer(Fifo<int> *fifo, unsigned n);
    ~FifoProducer();
    virtual void run();
};
