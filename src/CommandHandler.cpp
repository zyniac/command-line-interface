#include "CommandHandler.h"

CommandHandler::CommandHandler(unsigned int reserveSlots = PRERESERVE_COMMANDS)
{}

bool CommandHandler::registerCommand(Command* command)
{
    this->commands.push_back(command);
	return true;
}

bool CommandHandler::unregisterCommand(const char* invoke)
{
    auto itr = this->getCommandIterator(invoke);
    if (itr != this->end())
    {
        this->commands.erase(itr);
        return true;
    }
    else
    {
        return false;
    }
}

bool CommandHandler::unregisterCommand(Command* command)
{
    return this->unregisterCommand(command->getInvoke().c_str());
}

std::vector<Command*>::iterator CommandHandler::getCommandIterator(const char* invoke)
{
    for (std::vector<Command*>::iterator itr = this->commands.begin(); itr < this->commands.end(); itr++)
    {
        std::string commandInvoke = (*itr)->getInvoke();
        if (commandInvoke == invoke)
        {
            return itr;
        }
    }
    return this->end();
}

CommandHandler::~CommandHandler()
{
    for (auto command : commands)
    {
        this->unregisterCommand(command);
    }
}

std::vector<Command*>::iterator CommandHandler::begin()
{
    return this->commands.begin();
}

std::vector<Command*>::iterator CommandHandler::end()
{
    return this->commands.end();
}

Command* CommandHandler::getCommand(const char* invoke)
{
    auto itr = this->getCommandIterator(invoke);
    return *itr;
}