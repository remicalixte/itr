#include "Calculator.h"
#include "Request.h"

#ifndef CrunchReq_h_INCLUDED
#define CrunchReq_h_INCLUDED

class CrunchReq : public Request
{
private:
    double param;
    double result;
    Calculator calc;

public:
    CrunchReq(double param);
    ~CrunchReq();
    virtual void execute();
    double waitReturn();
};

#endif