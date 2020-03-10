#include "libtime.h"
#include "time.h"

class Chrono {
   private:
    timespec startTime_;
    timespec stopTime_;
    bool isActive_;

   public:
    Chrono(/* args */);
    ~Chrono();
    void stop();
    void restart();
    bool isActive();
    double startTime();
    double stopTime();
    double lap();
};
