#include "Semaphore.h"
#include "Thread.h"

class Consumer : public Thread {
   private:
    Semaphore& sema;

   public:
    Consumer(Semaphore& sema);
    ~Consumer();

   protected:
    virtual void run();
};