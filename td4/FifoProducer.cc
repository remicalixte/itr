#include "FifoProducer.h"

#include <stdio.h>

FifoProducer::FifoProducer(Fifo<int> *fifo, unsigned n) : fifo(fifo), n(n)
{
}

FifoProducer::~FifoProducer()
{
}

void FifoProducer::run()
{
    for (unsigned i = 0; i < n; i++)
    {
        fifo->push(i);
    }
}