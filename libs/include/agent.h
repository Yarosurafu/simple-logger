#ifndef AGENT_H
#define AGENT_H
#include <semaphore.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>

class Agent
{
public:
    bool retNull = false;

    void setSemOpenRetNull(bool val) { retNull = val; }

    virtual sem_t* a_sem_open(const char *name, int oflag,
                       mode_t mode, unsigned int value){ return (retNull) ? SEM_FAILED : sem_open(name, oflag, mode, value); }

    virtual char* a_strerror(int errnum){ return strerror(errnum); }

    virtual void a_exit(int status) { exit(status); }

    virtual int a_pthread_mutex_lock(pthread_mutex_t *mutex) { return pthread_mutex_lock(mutex); }

    virtual int a_pthread_mutex_unlock(pthread_mutex_t *mutex) { return pthread_mutex_unlock(mutex); }
};

#endif