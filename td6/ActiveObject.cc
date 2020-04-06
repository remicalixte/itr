#include "ActiveObject.h"

ActiveObject::ActiveObject(/* args */) {
}

ActiveObject::~ActiveObject() {
}

void ActiveObject::run() {
    while (!stopped) {
        printf("inside while\n");
        Request* req = reqFifo.pop();
        printf("popped\n");
        req->execute();
    }
}

void ActiveObject::stop() {
    stopped = true;
}