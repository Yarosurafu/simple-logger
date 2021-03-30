#ifndef AGENT_MOCK_H
#define AGENT_MOCK_H
#include "agent.h"
#include <gmock/gmock.h>

class AgentMock : public Agent
{
public:
    MOCK_METHOD(sem_t*, a_sem_open, (const char *name, int oflag, mode_t mode, unsigned int value), (override));
    MOCK_METHOD(char*, a_strerror, (int errnum), (override));
    MOCK_METHOD(void, a_exit, (int status), (override));
    MOCK_METHOD(int, a_pthread_mutex_lock, (pthread_mutex_t *mutex), (override));
    MOCK_METHOD(int, a_pthread_mutex_unlock, (pthread_mutex_t *mutex), (override));
};

#endif