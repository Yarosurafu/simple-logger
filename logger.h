#include <semaphore.h>
#include <string>

//RAII-class for sem manipulating
//and logging
class Logger
{
public:
    //enum for describing type of message
    enum MSG_TYPE
    {
        MSG_INFO,
        MSG_ERROR,
        MSG_WARNING,
        MAX_MSG                         //quantity of message types
    };

private:
    int _semDescriptor;                 //descriptor of semaphore
    sem_t* _sem;
    const char* _semName = "/cakeSem";  //name of semaphore

    /**
     * Converts MSG_TYPE to std::string
     * for logging
    */
    std::string _typeToStr(MSG_TYPE msgType);

public:
    Logger();
    Logger(const Logger& copyOf);
    void printLog(MSG_TYPE msgType, const std::string message);
    ~Logger();
};

void exitErr(const char* cause);