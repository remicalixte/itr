#include "Mutex.h"
#include "libtime.h"
#include "limits.h"

class Semaphore {
   private:
    unsigned counter;
    unsigned maxCount;
    Mutex mutex;

   public:
    Semaphore(unsigned iniCount = 0, unsigned maxCount = UINT_MAX);
    ~Semaphore();
    void give();
    void take();
    bool take(double timeout_ms);
};
