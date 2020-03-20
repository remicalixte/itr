#include <stdlib.h>

#include <vector>

#include "Incrementer.h"

using namespace std;
int main() {
    volatile double counter;
    int n = 20;
    int tasks = 30;
    vector<Incrementer> incrs;

    for (int i = 0; i < tasks; i++) {
        incrs.push_back(Incrementer(&counter, n));
        incrs[i].start();
    }

    // for (auto it = incrs.begin(); it != incrs.end(); it++) {
    //     while (it->)
    // }
}
