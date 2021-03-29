#include "mock.h"

#include <functional>

static std::function<int(sem_t*)> _sem_wait;

SemaphoreFuncsMock::SemaphoreFuncsMock()
{
    _sem_wait = [this](sem_t* sem)
                {
                    return sem_wait(sem);
                };
}

SemaphoreFuncsMock::~SemaphoreFuncsMock()
{
    _sem_wait = {};
}

extern "C"
{
    int sem_wait(sem_t* sem)
    {
        return _sem_wait(sem);
    }
}