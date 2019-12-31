#pragma once

#include <vector>
#include <string>
#include <algorithm>

class Argument
{
public:
    enum class ArgumentStatus
    {
        WRITTEN_OUT, COMPACT, INVALID
    };

    struct ArgumentData
    {
        std::vector<std::string> subarguments;
        std::string argument;
        ArgumentStatus status = ArgumentStatus::INVALID;
    };

private:
    ArgumentData data;

public:
	Argument() noexcept = default;
    Argument(Argument::ArgumentData data) noexcept;
    Argument(Argument&& argument) noexcept;
    Argument(Argument& argument) noexcept;
    Argument(const Argument& argument) noexcept;
    bool hasSubArgument(const std::string& argument);
    bool hasSubArguments();
    std::vector<std::string> getSubArguments();
    std::string getName();
    bool hasName(const std::string& arg);
    ArgumentStatus getStatus();
    std::vector<std::string>::iterator begin();
    std::vector<std::string>::iterator end();

};