#include <libtime.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <string>

using namespace std;
void incr(unsigned int nLoops, volatile double *pCounter, bool protect, pthread_mutex_t *mu);
void *call_incr(void *data);

struct call_incr_arg
{
    unsigned int nLoops;
    volatile double *pCounter;
    pthread_mutex_t mutex;
    bool protect;
};

void incr(unsigned int nLoops, volatile double *pCounter, bool protect, pthread_mutex_t *mu)
{
    if (protect)
    {
        pthread_mutex_lock(mu);
    }
    for (size_t i = 0; i < nLoops; i++)
    {
        (*pCounter)++;
    }
    if (protect)
    {
        pthread_mutex_unlock(mu);
    }
}

void *call_incr(void *data)
{
    call_incr_arg *args = (call_incr_arg *)data;
    incr(args->nLoops, args->pCounter, args->protect, &args->mutex);

    return NULL;
}

int set_sched(int schedPolicy, pthread_attr_t *attr)
{
    sched_param main_param = {
        sched_priority : sched_get_priority_max(schedPolicy),
    };
    int ret = pthread_setschedparam(pthread_self(), schedPolicy, &main_param);
    if (ret != 0)
    {
        return ret;
    }

    sched_param child_param;
    if (schedPolicy == SCHED_OTHER)
    {
        child_param.sched_priority = 0;
    }
    else
    {
        child_param.sched_priority = (sched_get_priority_max(schedPolicy) + sched_get_priority_min(schedPolicy)) / 2;
    }
    pthread_attr_init(attr);
    pthread_attr_setschedparam(attr, &child_param);

    return 0;
}

int main(int argc, char const *argv[])
{
    timespec start = timespec_now();

    if (argc < 3)
    {
        printf("needs a counter argument and task number\n");
        return 1;
    }

    volatile double counter = 0;
    unsigned int nLoops = stoi(argv[1]);
    unsigned nTasks = stoi(argv[2]);
    int schedPolicy = SCHED_OTHER;
    if (argc > 3)
    {
        schedPolicy = stoi(argv[3]);
    }
    bool protect = false;
    if (argc > 4)
    {
        protect = strlen(argv[3]) > 0;
    }

    pthread_attr_t attr;
    int ret = set_sched(schedPolicy, &attr);
    if (ret != 0)
    {
        printf("set_sched failed with: %d, if SCHED_RR is used, sudo is needed\n", ret);
        return 1;
    }

    call_incr_arg args = {
        nLoops : nLoops,
        pCounter : &counter,
        mutex : {},
        protect : protect,
    };
    pthread_mutex_init(&args.mutex, nullptr);

    pthread_t *tasks = (pthread_t *)malloc(nTasks * sizeof(pthread_t));
    for (size_t i = 0; i < nTasks; i++)
    {
        pthread_create(&tasks[i], &attr, call_incr, &args);
    }
    for (size_t i = 0; i < nTasks; i++)
    {
        pthread_join(tasks[i], NULL);
    }

    timespec end = timespec_now();

    printf("final counter value: %f\n", counter);
    printf("%d %d %lf\n", nLoops, nTasks, timespec_to_ms(end - start));
    free(tasks);
    pthread_attr_destroy(&attr);
    return 0;
}
