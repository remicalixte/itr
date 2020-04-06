#include "ActiveCalc.h"

ActiveCalc::ActiveCalc(/* args */) {
}

ActiveCalc::~ActiveCalc() {
}

CrunchReq* ActiveCalc::async_crunch(double param) {
    CrunchReq* req = new CrunchReq(param);
    reqFifo.push(req);
    return req;
}
