#include "mock.h"

#include <functional>

sem_operate_t _sem_wait = reinterpret_cast<sem_operate_t>(dlsym(RTLD_NEXT, "sem_wait"));
sem_operate_t _sem_post = reinterpret_cast<sem_operate_t>(dlsym(RTLD_NEXT, "sem_post"));
sem_operate_t _sem_close = reinterpret_cast<sem_operate_t>(dlsym(RTLD_NEXT, "sem_close"));
sem_unlink_t _sem_unlink = reinterpret_cast<sem_unlink_t>(dlsym(RTLD_NEXT, "sem_unlink"));

//----------Containers for lambdas with mock calls----------
static std::function<int(sem_t*)> g_sem_wait = reinterpret_cast<sem_operate_t>(dlsym(RTLD_NEXT, "sem_wait"));
static std::function<int(sem_t*)> g_sem_post = reinterpret_cast<sem_operate_t>(dlsym(RTLD_NEXT, "sem_post"));
static std::function<int(sem_t*)> g_sem_close = reinterpret_cast<sem_operate_t>(dlsym(RTLD_NEXT, "sem_close"));
static std::function<int(const char*)> g_sem_unlink = reinterpret_cast<sem_unlink_t>(dlsym(RTLD_NEXT, "sem_unlink"));
//--------------------------------------------------------

//--------------------------------------------------------
SemaphoreFuncsMock::SemaphoreFuncsMock()
{
    g_sem_wait = [this](sem_t* sem)
                {
                    return sem_wait(sem);
                };

    g_sem_post = [this](sem_t* sem)
                {
                    return sem_post(sem);
                };

    g_sem_close = [this](sem_t* sem)
                {
                    return sem_close(sem);
                };

    g_sem_unlink = [this](const char* name)
                {
                    return sem_unlink(name);
                };
}
//--------------------------------------------------------

//TODO: write real function addresses
SemaphoreFuncsMock::~SemaphoreFuncsMock()
{
    g_sem_wait = _sem_wait;
    g_sem_post = _sem_post;
    g_sem_close = _sem_close;
    g_sem_unlink = _sem_unlink;
}

//--------------------------------------------------------
//Redefinition of real functions
extern "C"
{
    int sem_wait(sem_t* sem)
    {
        return g_sem_wait(sem);
    }

    int sem_post(sem_t* sem)
    {
        return g_sem_post(sem);
    }

    int sem_close(sem_t* sem)
    {
        return g_sem_close(sem);
    }

    int sem_unlink(const char* name)
    {
        return g_sem_unlink(name);
    }
}
//--------------------------------------------------------