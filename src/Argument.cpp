#include "Argument.h"

Argument::Argument(Argument&& argument) noexcept
    : data(std::move(argument.data))
{}

Argument::Argument(Argument& argument) noexcept
    : data(argument.data)
{}

Argument::Argument(Argument::ArgumentData data) noexcept
    : data(data)
{}

Argument::Argument(const Argument& argument) noexcept
    : data(data)
{}

bool Argument::hasSubArgument(const std::string& argument)
{
    return std::find(this->data.subarguments.begin(), this->data.subarguments.end(), argument) != this->data.subarguments.end();
}

bool Argument::hasSubArguments()
{
    return this->data.subarguments.size() > 0;
}

std::vector<std::string> Argument::getSubArguments()
{
    return this->data.subarguments;
}

std::string Argument::getName()
{
    return this->data.argument;
}

bool Argument::hasName(const std::string& arg)
{
    return arg == this->data.argument;
}

Argument::ArgumentStatus Argument::getStatus()
{
    return this->data.status;
}

std::vector<std::string>::iterator Argument::begin()
{
    return this->data.subarguments.begin();
}

std::vector<std::string>::iterator Argument::end()
{
    return this->data.subarguments.end();
}