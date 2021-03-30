#ifndef MOCK_H
#define MOCK_H
#include <gmock/gmock.h>
#include <semaphore.h>
#include <pthread.h>

class SemaphoreFuncsMock
{
public:
    SemaphoreFuncsMock();
    ~SemaphoreFuncsMock();

    MOCK_METHOD(int, sem_wait, (sem_t* sem));
    MOCK_METHOD(int, sem_post, (sem_t* sem));
    MOCK_METHOD(int, sem_close, (sem_t* sem));
    MOCK_METHOD(int, sem_unlink, (const char* name));
};

#endif