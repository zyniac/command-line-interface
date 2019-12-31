#pragma once

#include <string>

class Command
{
protected:
    std::string invoke;

public:
    Command(const char* command);
    std::string&& getInvoke();
    virtual bool run() = 0;
};