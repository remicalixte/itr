#include "ActiveObject.h"

ActiveObject::ActiveObject(/* args */) {
}

ActiveObject::~ActiveObject() {
}

void ActiveObject::run() {
    while (!stopped) {
        Request* req = reqFifo.pop(1000);
        if (req != nullptr) {
        req->execute();
        }
    }
}

void ActiveObject::stop() {
    stopped = true;
}