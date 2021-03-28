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
void exitErr(const std::string& cause)
{
    std::cerr << "ERROR: " << cause << std::endl;
    std::cerr << strerror(errno) << std::endl;
    exit(EXIT_FAILURE);
}
//--------------------------------------------------