#include "logger.h"

#include <iostream>
#include <string.h>//for strerror
#include <fcntl.h>//for O_* constants
#include <unistd.h>//for getpid()

//--------------------------------------------------
/**
 * Function for displaying error cause,
 * value of errno and then exit with
 * EXIT_FAILURE
 * 
 * @param cause Cause of exiting the app
 */
void exitErr(const char* cause)
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
        case Logger::MSG_INFO: return "----------{ INFO }------------\n";

        case Logger::MSG_ERROR: return "XXXXXXXXXXX{ ERROR }XXXXXXXXXXX\n";

        case Logger::MSG_WARNING: return "!!!!!!!!!!{ WARNING }!!!!!!!!!!\n";
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
    _sem = sem_open(_semName, O_CREAT, 0666, 1);
    if(_sem == SEM_FAILED) exitErr("sem_open failed");
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
void Logger::printLog(MSG_TYPE msgType, const std::string message)
{
    sem_wait(_sem);
    std::cout << _typeToStr(msgType);
    std::cout << "PROCESS WITH PID -->" << getpid() << "\n";
    std::cout << message;
    std::cout << "\n####################\n\n\n";
    sem_post(_sem);
}
//--------------------------------------------------

//--------------------------------------------------
/**
 * Destructor of RAII-class for POSIX-sem.
 * 
 * First of all, process need to close the semaphore.
 * Then, unlinking the named semaphore referred to by name.
    The semaphore is destroyed once all other processes that
    have the semaphore open close it.
 */
Logger::~Logger()
{
    sem_close(_sem);
    sem_unlink(_semName);
}
//--------------------------------------------------