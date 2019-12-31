#pragma once

#include <vector>
#include "Command.h"

class CommandHandler
{
private:
    std::vector<Command*> commands;

public:
	CommandHandler() = default;
    CommandHandler(unsigned int reserveSlots);
    ~CommandHandler();
    bool registerCommand(Command* command);
    bool unregisterCommand(Command* command);
    bool unregisterCommand(const char* invoke);
    Command* getCommand(const char* invoke);
    std::vector<Command*>::iterator getCommandIterator(const char* invoke);
    std::vector<Command*>::iterator begin();
    std::vector<Command*>::iterator end();

};