#include "Looper.h"

Looper::Looper(/* args */) {
}

Looper::~Looper() {
}

double Looper::runLoop(double nLoops) {
    double counter = 0;
    for (iLoop = 0; !(doStop) && iLoop < nLoops; iLoop++) {
        counter++;
    }

    return iLoop;
}

double Looper::getSample() {
    return iLoop;
}

double Looper::stopLoop() {
    doStop = true;
    return iLoop;
}