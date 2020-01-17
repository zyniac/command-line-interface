#pragma once

#include <vector>
#include "Argument.h"

class ArgumentList
{
private:
    std::vector<Argument> arguments;
    bool valid;
	std::string invoke;

public:
    ArgumentList() noexcept = delete;
    ArgumentList(std::string&& invoke) noexcept;
    ArgumentList(ArgumentList&& al) noexcept;
    bool push(Argument&& argument);
    bool isValid();
    size_t getArgument(const char* name);
    bool isArgument(const char* name);
    bool hasArgument(const char* name);
    void setInvalid();
    Argument& operator[](size_t count);
    size_t size();
    std::string getInvoke();
    std::vector<Argument>::iterator begin();
    std::vector<Argument>::iterator end();

};