#ifndef ERROR_HANDLE_H
#define ERROR_HANDLE_H
#include <string>

#include "agent.h"

void exitErr(const std::string& cause, Agent& agent);
#endif