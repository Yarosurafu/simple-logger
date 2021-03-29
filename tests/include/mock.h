#ifndef MOCK_H
#define MOCK_H
#include <gmock/gmock.h>
#include <semaphore.h>

class SemaphoreFuncsMock
{
public:
    SemaphoreFuncsMock();
    ~SemaphoreFuncsMock();
    MOCK_METHOD(int, sem_wait, (sem_t* sem));
};

#endif