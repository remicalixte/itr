#include "ActiveObject.h"

ActiveObject::ActiveObject(/* args */) {
}

ActiveObject::~ActiveObject() {
}

void ActiveObject::run() {
    while (!stopped) {
        Request* req = reqFifo.pop();
        req->execute();
    }
}

void ActiveObject::stop() {
    stopped = true;
}