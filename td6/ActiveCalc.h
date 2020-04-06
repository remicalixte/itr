#ifndef ActiveCalc_h_INCLUDED
#define ActiveCalc_h_INCLUDED

#include "ActiveObject.h"
#include "CrunchReq.h"
#include "Fifo.hh"

class ActiveCalc : public ActiveObject {
   private:
    /* data */
   public:
    ActiveCalc(/* args */);
    ~ActiveCalc();
    CrunchReq* async_crunch(double param);
};

#endif