#include "Semaphore.h"
#include "Thread.h"

class Producer : public Thread {
   private:
    Semaphore& sema;

   public:
    Producer(Semaphore& sema);
    ~Producer();

   protected:
    virtual void run();
};