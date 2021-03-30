#include "error_handle.h"

#include <iostream>
#include <string.h>

//--------------------------------------------------
/**
 * Function for displaying error cause,
 * value of errno and then exit with
 * EXIT_FAILURE
 * 
 * @param cause Cause of exiting the app
 */
void exitErr(const std::string& cause, Agent& agent)
{
    std::cerr << "ERROR: " << cause << std::endl;
    std::cerr << agent.a_strerror(errno) << std::endl;
    agent.a_exit(EXIT_FAILURE);
}
//--------------------------------------------------