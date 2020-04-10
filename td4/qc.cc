#include <iostream>
#include <vector>

#include "Consumer.h"
#include "Producer.h"
#include "Semaphore.h"

using namespace std;

int main()
{
    Semaphore sema = Semaphore();

    unsigned nCons = 11;
    unsigned nProds = 35;

    vector<Consumer *>
        cons(nCons);
    vector<Producer *> prods(nProds);

    for (size_t i = 0; i < nCons; i++)
    {
        cons[i] = new Consumer(sema);
        cons[i]->start();
    }
    for (size_t i = 0; i < nProds; i++)
    {
        prods[i] = new Producer(sema);
        prods[i]->start();
    }

    for (size_t i = 0; i < nCons; i++)
    {
        cons[i]->join();
    }
    for (size_t i = 0; i < nProds; i++)
    {
        prods[i]->join();
    }

    for (size_t i = 0; i < nCons; i++)
    {
        delete cons[i];
    }
    for (size_t i = 0; i < nProds; i++)
    {
        delete prods[i];
    }

    cout << "final semaphore counter value: " << sema.getCounter() << endl;

    return 0;
}
