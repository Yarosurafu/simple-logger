#ifndef LOGGER_H
#define LOGGER_H
#include <semaphore.h>
#include <string>
#include <agent.h>

//RAII-class for sem manipulating
//and logging
class Logger
{
public:
    //enum for describing type of message
    enum class MSG_TYPE
    {
        MSG_INFO,
        MSG_ERROR,
        MSG_WARNING,
        MAX_MSG                         //quantity of message types
    };

public:
    static Logger* getInstance(Agent& agent);
    void printLog(MSG_TYPE msgType, const std::string& message);
    static void deleteInstance();
    ~Logger();

private:
    Logger(Agent& agent);
    
    /**
     * Converts MSG_TYPE to std::string
     * for logging
    */
    std::string _typeToStr(MSG_TYPE msgType);

private:
    static Logger* _loggerInstance;
    sem_t* _semaphore = nullptr;
    const char* _semaphoreName = "/logSemaphore";  //name of semaphore
};
#endif