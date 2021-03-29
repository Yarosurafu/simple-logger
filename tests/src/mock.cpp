#include "mock.h"

#include <functional>

static std::function<int(sem_t*)> _sem_wait;
static std::function<int(sem_t*)> _sem_post;

SemaphoreFuncsMock::SemaphoreFuncsMock()
{
    _sem_wait = [this](sem_t* sem)
                {
                    return sem_wait(sem);
                };

    _sem_post = [this](sem_t* sem)
                {
                    return sem_post(sem);
                };
}

SemaphoreFuncsMock::~SemaphoreFuncsMock()
{
    _sem_wait = {};
    _sem_post = {};
}

extern "C"
{
    int sem_wait(sem_t* sem)
    {
        return _sem_wait(sem);
    }

    int sem_post(sem_t* sem)
    {
        return _sem_post(sem);
    }
}