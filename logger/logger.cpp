#include "logger.h"

#include <iostream>
#include <string.h> //for strerror
#include <fcntl.h>  //for O_* constants
#include <unistd.h> //for getpid()

//--------------------------------------------------
/**
 * Function for displaying error cause,
 * value of errno and then exit with
 * EXIT_FAILURE
 * 
 * @param cause Cause of exiting the app
 */
void exitErr(const std::string& cause)
{
    std::cerr << "ERROR: " << cause << std::endl;
    std::cerr << strerror(errno) << std::endl;
    exit(EXIT_FAILURE);
}
//--------------------------------------------------

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
Logger::Logger()
{
    const mode_t permissions = 0666;
    const short semaphoreStartValue = 1;
    _semaphore = sem_open(_semName, O_CREAT, permissions, semaphoreStartValue);
    if(_semaphore == SEM_FAILED)
        exitErr("sem_open failed");
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
    std::cout << "\n####################\n\n\n";
    sem_post(_semaphore);
}
//--------------------------------------------------

//--------------------------------------------------
/**
 * Destructor of RAII-class for POSIX-sem.
 */
Logger::~Logger()
{
    sem_close(_semaphore);
    sem_unlink(_semName);
}
//--------------------------------------------------