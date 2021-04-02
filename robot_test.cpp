#include "agent.h"
#include "logger.h"

#include <iostream>
#include <string.h>
#include <pthread.h>

void* logFromThread(void* arg)
{
    Agent agent;
    Logger::getInstance(agent)->printLog(Logger::MSG_TYPE::MSG_INFO, "msg\n");
}

int main(int argc, char** argv)
{
    Agent agent;
    //Correct getInstance() test (ci - correct instance)
    if(!strcmp(argv[1], "-ci"))
    {
        Logger* instance = Logger::getInstance(agent);
        if(instance != nullptr)
            std::cout << "instance != nullptr";
    }
    //Incorrect getInstance() test (ni - null instance)
    else if(!strcmp(argv[1], "-ni"))
    {
        agent.setSemOpenRetNull(true);
        Logger* instance = Logger::getInstance(agent);
        if(instance != nullptr)
            std::cout << "instance != nullptr";
    }

    //Info message (im - info message)
    else if(!strcmp(argv[1], "-im"))
    {
        Logger::getInstance(agent)->printLog(Logger::MSG_TYPE::MSG_INFO, "msg\n");
    }

    //Error message (em - error message)
    else if(!strcmp(argv[1], "-em"))
    {
        Logger::getInstance(agent)->printLog(Logger::MSG_TYPE::MSG_ERROR, "msg\n");
    }

    //Warning message (wm - warning message)
    else if(!strcmp(argv[1], "-wm"))
    {
        Logger::getInstance(agent)->printLog(Logger::MSG_TYPE::MSG_WARNING, "msg\n");
    }

    else if(!strcmp(argv[1], "-t"))
    {
        int SIZE = atoi(argv[2]);
        pthread_t* tids = new pthread_t[SIZE];
        for(int i = 0; i < SIZE; ++i)
        {
            pthread_create(&tids[i], nullptr, logFromThread, nullptr);
        }

        for(int i = 0; i < SIZE; ++i)
        {
            void* retVal;
            pthread_join(tids[i], &retVal);
        }
    }

    return 0;
}