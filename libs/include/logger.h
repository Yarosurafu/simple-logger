#ifndef LOGGER_H
#define LOGGER_H
#include <semaphore.h>
#include <string>

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
    static Logger* getInstance();
    void printLog(MSG_TYPE msgType, const std::string& message);
    ~Logger();

private:
    /**
     * Converts MSG_TYPE to std::string
     * for logging
    */
    std::string _typeToStr(MSG_TYPE msgType);
    Logger();

private:
    static Logger* _loggerInstance;
    sem_t* _semaphore = nullptr;
    const char* _semaphoreName = "/logSemaphore";  //name of semaphore
};
#endif