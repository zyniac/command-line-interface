#include "Command.h"

Command::Command(const char* command)
{
    this->invoke = std::string(command);
}

std::string&& Command::getInvoke()
{
    return std::move(std::string(this->invoke));
}