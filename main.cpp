#include <pthread.h>//for threads
#include <string>
#include <iostream>
#include <unistd.h> //for fork(), usleep()
#include <cstdlib>  //for rand(), srand()
#include <ctime>    //for time()

#include "logger.h"

//Object of RAII-class that represents logger
Logger log;

//-----Func prototypes-----
void* logFromThread(void* arg);
int getRandomNumber(int min, int max);
//-------------------------

int main()
{
    srand(static_cast<unsigned int>(time(0)));  //Set seed for rand()
    pthread_t tids[Logger::MAX_MSG];            //An array for containing thread_id

    //--------------------------------
    //Cycle of generating log-messages
    while(true)
    {
        //Logging all types of messages
        for(size_t i = 0; i < Logger::MAX_MSG; ++i)
        {
            Logger::MSG_TYPE* arg = new Logger::MSG_TYPE;
            *arg = static_cast<Logger::MSG_TYPE>(i);
            pthread_create(&tids[i], nullptr, logFromThread, static_cast<void*>(arg));
        }
        //Sleep of main thread before generating new logs
        usleep(getRandomNumber(1000, 999999));
    }
    //--------------------------------
}//END OF MAIN

//----------------------------------------------------------------------------------------------
/**
 * Function for threads that calls printLog()
 * 
 * @param arg Type of message for logging
 */
void* logFromThread(void* arg)
{
    Logger::MSG_TYPE* threadNum = static_cast<Logger::MSG_TYPE*>(arg);
    log.printLog(static_cast<Logger::MSG_TYPE>(*threadNum), 
                    std::string("Thread " + std::to_string(*threadNum) + " writing into log"));
    delete threadNum;
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