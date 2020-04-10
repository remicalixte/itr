#include <iostream>
#include "Client.h"
#include "ActiveCalc.h"
#include "CrunchReq.h"

Client::Client(double crunchSeed, ActiveCalc *activeCalc) : crunchSeed(crunchSeed), activeCalc(activeCalc){};

void Client::run()
{
    CrunchReq *crunchReq = activeCalc->async_crunch(crunchSeed);
    double result = crunchReq->waitReturn();
    std::cout << "Client " << crunchSeed << " result " << result << std::endl;
}
