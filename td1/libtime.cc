#include "libtime.h"

double timespec_to_ms(const timespec& time_ts) {
    double time_ms = 0;
    time_ms += ((double)time_ts.tv_nsec) / 1000000;
    time_ms += time_ts.tv_sec * 1000;

    return time_ms;
}

timespec timespec_from_ms(double time_ms) {
    timespec time_ts;
    time_ts.tv_sec = time_ms / 1000;
    time_ms -= ((long)(time_ms / 1000)) * 1000;
    time_ms *= 1000000;
    time_ts.tv_nsec = ((long)time_ms);
    if (time_ts.tv_nsec < 0) {
        time_ts.tv_nsec += 1000000000;
        time_ts.tv_sec--;
    }

    return time_ts;
}

timespec timespec_now() {
    timespec time_ts;
    clock_gettime(CLOCK_REALTIME, &time_ts);

    return time_ts;
}

timespec timespec_negate(const timespec& time_ts) {
    timespec negative;
    negative.tv_sec = -time_ts.tv_sec;
    if (time_ts.tv_nsec > 0) {
        negative.tv_nsec = 1000000000 - time_ts.tv_nsec;
        negative.tv_sec--;
    }

    return negative;
}

timespec timespec_add(const timespec& time1_ts, const timespec& time2_ts) {
    timespec sum;
    sum.tv_sec = time1_ts.tv_sec + time2_ts.tv_sec;
    sum.tv_nsec = time1_ts.tv_nsec + time2_ts.tv_nsec;
    if (sum.tv_nsec > 1000000000) {
        sum.tv_nsec -= 1000000000;
        sum.tv_sec++;
    }

    return sum;
}

timespec timespec_subtract(const timespec& time1_ts, const timespec& time2_ts) {
    timespec diff;
    diff.tv_sec = time1_ts.tv_sec - time2_ts.tv_sec;
    diff.tv_nsec = time1_ts.tv_nsec - time2_ts.tv_nsec;
    if (diff.tv_nsec < 0) {
        diff.tv_nsec += 1000000000;
        diff.tv_sec--;
    }

    return diff;
}

timespec timespec_wait(const timespec& delay_ts) {
    timespec remaining;
    nanosleep(&delay_ts, &remaining);
    int i = nanosleep(&delay_ts, &remaining);
    // If nanosleep is interrupted
    if (i == -1)
    {
        timespec_wait(remaining);
    }

    return remaining;
}

timespec operator+(const timespec& time1_ts, const timespec& time2_ts) {
    return timespec_add(time1_ts, time2_ts);
}

timespec operator-(const timespec& time1_ts, const timespec& time2_ts) {
    return timespec_subtract(time1_ts, time2_ts);
}

timespec& operator+=(timespec& time_ts, const timespec& delay_ts) {
    timespec sum = timespec_add(time_ts, delay_ts);
    time_ts.tv_sec = sum.tv_sec;
    time_ts.tv_nsec = sum.tv_nsec;

    return time_ts;
}

timespec& operator-=(timespec& time_ts, const timespec& delay_ts) {
    timespec diff = timespec_subtract(time_ts, delay_ts);
    time_ts.tv_sec = diff.tv_sec;
    time_ts.tv_nsec = diff.tv_nsec;

    return time_ts;
}

bool operator==(const timespec& time1_ts, const timespec& time2_ts) {
    return (time1_ts.tv_sec == time2_ts.tv_sec) && (time1_ts.tv_nsec == time2_ts.tv_nsec);
}
bool operator!=(const timespec& time1_ts, const timespec& time2_ts) {
    return !(time1_ts == time2_ts);
}
bool operator<(const timespec& time1_ts, const timespec& time2_ts) {
    return (time1_ts.tv_sec < time2_ts.tv_sec) || ((time1_ts.tv_sec == time2_ts.tv_sec) && time1_ts.tv_nsec < time2_ts.tv_nsec);
}
bool operator>(const timespec& time1_ts, const timespec& time2_ts) {
    return (time1_ts.tv_sec > time2_ts.tv_sec) || ((time1_ts.tv_sec == time2_ts.tv_sec) && time1_ts.tv_nsec > time2_ts.tv_nsec);
}