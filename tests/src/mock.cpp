#include "mock.h"

#include <functional>

static std::function<int(sem_t*)> _sem_wait;
static std::function<int(sem_t*)> _sem_post;
static std::function<int(sem_t*)> _sem_close;
static std::function<int(const char*)> _sem_unlink;

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
    _sem_close = [this](sem_t* sem)
                {
                    return sem_close(sem);
                };
    _sem_unlink = [this](const char* name)
                {
                    return sem_unlink(name);
                };
}

SemaphoreFuncsMock::~SemaphoreFuncsMock()
{
    _sem_wait = {};
    _sem_post = {};
    _sem_close = {};
    _sem_unlink = {};
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

    int sem_close(sem_t* sem)
    {
        return _sem_close(sem);
    }

    int sem_unlink(const char* name)
    {
        return _sem_unlink(name);
    }
}