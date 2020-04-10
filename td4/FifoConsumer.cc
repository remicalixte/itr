#include "FifoConsumer.h"

FifoConsumer::FifoConsumer(Fifo<int> *fifo, Mutex *mu, volatile unsigned *counter) : fifo(fifo), mu(mu), counter(counter)
{
}

FifoConsumer::~FifoConsumer()
{
}

void FifoConsumer::run()
{
    while (true)
    {
        unsigned i = fifo->pop();
        {
            auto lock = Mutex::Lock(*mu);
            (*counter) += i;
        }
    }
}

void FifoConsumer::stop()
{
    stop_ = true;
}