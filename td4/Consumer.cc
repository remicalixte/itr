#include "Consumer.h"

Consumer::Consumer(Semaphore &sema) : sema(sema)
{
}

Consumer::~Consumer()
{
}

void Consumer::run()
{
    sema.take();
}