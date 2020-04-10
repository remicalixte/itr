#ifndef Client_h_INCLUDED
#define Client_h_INCLUDED

#include "Thread.h"
#include "ActiveCalc.h"

class Client : public Thread
{
public:
    Client(double crunchSeed, ActiveCalc *activeCalc);

protected:
    void run() override;

private:
    double crunchSeed;
    ActiveCalc *activeCalc;
};

#endif