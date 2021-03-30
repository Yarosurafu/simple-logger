#ifndef MOCK_H
#define MOCK_H
#include <gmock/gmock.h>
#include <semaphore.h>
#include <pthread.h>
#include <dlfcn.h>

using sem_operate_t = int(*)(sem_t*);
using sem_unlink_t = int(*)(const char*);

class SemaphoreFuncsMock
{
public:
    SemaphoreFuncsMock();
    ~SemaphoreFuncsMock();

    MOCK_METHOD(int, sem_wait, (sem_t* sem));
    MOCK_METHOD(int, sem_post, (sem_t* sem));
    MOCK_METHOD(int, sem_close, (sem_t* sem));
    MOCK_METHOD(int, sem_unlink, (const char* name));

private:
    std::function<int(sem_t*)> _sem_wait = reinterpret_cast<sem_operate_t>(dlsym(RTLD_NEXT, "sem_wait"));
    std::function<int(sem_t*)> _sem_post = reinterpret_cast<sem_operate_t>(dlsym(RTLD_NEXT, "sem_post"));
    std::function<int(sem_t*)> _sem_close = reinterpret_cast<sem_operate_t>(dlsym(RTLD_NEXT, "sem_close"));
    std::function<int(const char*)> _sem_unlink = reinterpret_cast<sem_unlink_t>(dlsym(RTLD_NEXT, "sem_unlink"));
};

#endif