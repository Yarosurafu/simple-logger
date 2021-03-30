#include "logger.h"
#include "error_handle.h"

#include <iostream>
#include <fcntl.h>  //for O_* constants
#include <unistd.h> //for getpid()
#include <pthread.h>

Logger* Logger::_loggerInstance = nullptr;

Logger* Logger::getInstance(Agent& agent)
{
    static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

    agent.a_pthread_mutex_lock(&mutex);
    if(_loggerInstance == nullptr)
        _loggerInstance = new Logger(agent);
    agent.a_pthread_mutex_unlock(&mutex);

    return _loggerInstance;
}

//--------------------------------------------------
/**
 * Converts MSG_TYPE to std::string 
 * for logging
 * 
 * @param msgType Type of message for
 *                  converting
 * 
 * @return std::string, which represents message type
*/
std::string Logger::_typeToStr(MSG_TYPE msgType)
{
    switch(msgType)
    {
        case MSG_TYPE::MSG_INFO: return "----------{ INFO }------------\n";

        case MSG_TYPE::MSG_ERROR: return "XXXXXXXXXXX{ ERROR }XXXXXXXXXXX\n";

        case MSG_TYPE::MSG_WARNING: return "!!!!!!!!!!{ WARNING }!!!!!!!!!!\n";
    }
}
//--------------------------------------------------

//--------------------------------------------------
/**
 * Constructor of RAII-class for POSIX-sem.
 * Opens semaphore
 */
Logger::Logger(Agent& agent)
{
    const mode_t permissions = 0666;
    const short semaphoreStartValue = 1;
    _semaphore = agent.a_sem_open(_semaphoreName, O_CREAT, permissions, semaphoreStartValue);
    if(_semaphore == SEM_FAILED)
        exitErr("sem_open failed", agent);
}
//--------------------------------------------------

//--------------------------------------------------
/**
 * Writing into log. First of all, this method 
 * logs message type and then message
 * 
 * @param msgType Type of displaying message
 * @param message Message for logging
 */
void Logger::printLog(MSG_TYPE msgType, const std::string& message)
{
    sem_wait(_semaphore);
    std::cout << _typeToStr(msgType);
    std::cout << "PROCESS ID -->" << getpid() << std::endl;
    std::cout << "THREAD ID -->" << pthread_self() << std::endl;
    std::cout << message;
    std::cout << "####################" << std::endl << std::endl << std::endl;
    sem_post(_semaphore);
}
//--------------------------------------------------

void Logger::deleteInstance()
{
    delete _loggerInstance;
    _loggerInstance = nullptr;
}

//--------------------------------------------------
/**
 * Destructor of RAII-class for POSIX-sem.
 */
Logger::~Logger()
{
    sem_close(_semaphore);
    sem_unlink(_semaphoreName);
    std::cout << "-->Destructor was called..." << std::endl;
}
//--------------------------------------------------