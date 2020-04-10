#include "CrunchReq.h"

CrunchReq::CrunchReq(double param) : param(param)
{
}

CrunchReq::~CrunchReq()
{
}

void CrunchReq::execute()
{
    result = calc.crunch(param);
    returnSema.give();
}

double CrunchReq::waitReturn()
{
    returnSema.take();
    return result;
}
