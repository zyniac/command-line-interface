#include "ArgumentList.h"

ArgumentList::ArgumentList(std::string&& invoke) noexcept
    : invoke(invoke),
    valid(true)
{}

ArgumentList::ArgumentList(ArgumentList&& al) noexcept
    : arguments(std::move(al.arguments)),
    valid(std::move(al.valid)),
    invoke(std::move(al.invoke))
{}

bool ArgumentList::push(Argument&& argument)
{
    arguments.emplace_back(argument);
	return true;
}

bool ArgumentList::isValid()
{
    return this->valid;
}

size_t ArgumentList::getArgument(const char* name)
{
    std::vector<Argument>::iterator itr = std::find_if(this->arguments.begin(), this->arguments.end(), [&](Argument& arg) {
        return arg.hasName(std::string(name));
    });
    return itr - this->arguments.begin();
}

bool ArgumentList::isArgument(const char* name)
{
    return this->getArgument(name) < arguments.size();
}

void ArgumentList::setInvalid()
{
    this->valid = false;
}

Argument& ArgumentList::operator[](size_t count)
{
    return this->arguments[count];
}

size_t ArgumentList::size()
{
    return this->arguments.size();
}

std::vector<Argument>::iterator ArgumentList::begin()
{
    return this->arguments.begin();
}

std::vector<Argument>::iterator ArgumentList::end()
{
    return this->arguments.end();
}

std::string ArgumentList::getInvoke()
{
    return this->invoke;
}

bool ArgumentList::hasArgument(const char* name)
{
    return this->isArgument(name);
}