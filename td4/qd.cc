#include <iostream>
#include <vector>

#include "Fifo.hh"
#include "FifoConsumer.h"
#include "FifoProducer.h"
#include "Mutex.h"

using namespace std;

int main() {
    Fifo<int> fifo;
    Mutex mu = Mutex();

    unsigned nCons = 11;
    unsigned nProds = 3;

    unsigned n = 5;
    volatile unsigned counter = 0;

    vector<FifoConsumer*>
        cons(nCons);
    vector<FifoProducer*> prods(nProds);

    for (size_t i = 0; i < nCons; i++) {
        cons[i] = new FifoConsumer(&fifo, &mu, &counter);
        cons[i]->start();
    }
    for (size_t i = 0; i < nProds; i++) {
        prods[i] = new FifoProducer(&fifo, n);
        prods[i]->start();
    }
    for (size_t i = 0; i < nProds; i++) {
        prods[i]->join();
    }
    for (size_t i = 0; i < nProds; i++) {
        delete prods[i];
    }

    while (counter < ((n * (n - 1)) / 2) * nProds) {
        //wait for total value
    }

    for (size_t i = 0; i < nCons; i++) {
        delete cons[i];
    }

    cout << "final counter value: " << counter << endl;
    exit(0);

    return 0;
}
