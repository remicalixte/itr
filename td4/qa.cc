#include <iostream>
#include <vector>

#include "Incrementer.h"

using namespace std;
int main()
{
    volatile double counter = 0;
    int n = 30000;
    unsigned tasks = 10;
    vector<Incrementer *> incrs;
    for (size_t i = 0; i < tasks; i++)
    {
        incrs.push_back(new Incrementer(&counter, n));
        incrs[i]->start();
    }

    for (auto it = incrs.begin(); it != incrs.end(); it++)
    {
        (*it)->join();
    }

    for (auto it = incrs.begin(); it != incrs.end(); it++)
    {
        delete (*it);
    }

    std::cout << "count value: " << counter << std::endl;
}