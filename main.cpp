#include <pthread.h>//for threads
#include <string>
#include <iostream>
#include <unistd.h> //for fork(), usleep()
#include <cstdlib>  //for rand(), srand()
#include <ctime>    //for time()

#include "logger.h"
#include "error_handle.h"

//-----Func prototypes-----
void* logFromThread(void* arg);
int getRandomNumber(int min, int max);
void codeForProcess();
//-------------------------

int main()
{
    srand(static_cast<unsigned int>(time(0)));  //Set seed for rand()

    switch(fork())
    {
        case -1:
        {
            exitErr("fork()");
        }
        break;

        case 0:
        {//Code for child process
            codeForProcess();
        }
        break;

        default:
        {//Code for parent process
            codeForProcess();
        }
        break;
    }    
}//END OF MAIN

//----------------------------------------------------------------------------------------------
/**
 * Function for threads that calls printLog()
 * 
 * @param arg Type of message for logging
 */
void* logFromThread(void* arg)
{
    Logger::MSG_TYPE* messageType = static_cast<Logger::MSG_TYPE*>(arg);
    std::string message = "Thread " + std::to_string(static_cast<int>(*messageType)) + " writing into log\n";
    Logger::getInstance()->printLog(*messageType, message);
    delete messageType;
}
//----------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------
/**
 * Function for generating random number in range [min, max]
 */
int getRandomNumber(int min, int max)
{
    static const double fraction = 1.0 / (static_cast<double>(RAND_MAX) + 1.0); 
    return static_cast<int>(rand() * fraction * (max - min + 1) + min);
}
//----------------------------------------------------------------------------------------------

void codeForProcess()
{
    const int QUANTITY_OF_MSG_TYPES = static_cast<int>(Logger::MSG_TYPE::MAX_MSG);
    pthread_t tids[QUANTITY_OF_MSG_TYPES];      //An array for containing thread_id
    
    //--------------------------------
    //Cycle of generating log-messages
    while(true)
    {
        //Logging all types of messages
        for(size_t i = 0; i < QUANTITY_OF_MSG_TYPES; ++i)
        {
            Logger::MSG_TYPE* arg = new Logger::MSG_TYPE;
            *arg = static_cast<Logger::MSG_TYPE>(i);
            if(pthread_create(&tids[i], nullptr, logFromThread, static_cast<void*>(arg)))
                delete arg;
        }
        //Sleep of main thread before generating new logs
        usleep(getRandomNumber(1000, 999999));
    }
    //--------------------------------
}