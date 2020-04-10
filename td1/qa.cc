#include <assert.h>
#include <unistd.h>

#include "libtime.h"

int main()
{
    timespec now = timespec_now();
    timespec now2 = timespec_from_ms(timespec_to_ms(now));
    assert(now - now2 < timespec_from_ms(0.0001) || now2 - now < timespec_from_ms(0.0001));

    sleep(1);
    timespec after = timespec_now();
    assert(now - after < timespec_from_ms(0));
    assert(after - now > timespec_from_ms(0));
    assert(after - after == timespec_from_ms(0));
    assert(after != now);
    return 0;
}
