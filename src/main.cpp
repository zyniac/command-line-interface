#include <iostream>
#include "ArgumentList.h"
#include "Interpreter.h"

int main(int argc, char** argv) {
    while (true)
    {
        std::cout << "CMD >> ";
        std::string input;
        std::getline(std::cin, input);
        ArgumentList al = Interpreter::compileCommand(input);

        if (al.isValid())
        {
            std::cout << "Command Name: " << al.getInvoke() << std::endl;
            for (auto argument : al)
            {
                std::cout << "Found Argument: " << argument.getName() << " - " << (argument.getStatus() == Argument::ArgumentStatus::COMPACT ? "COMPACT" : "WRITTEN OUT") << std::endl;
                for (auto subarg : argument)
                {
                    std::cout << "Found Subargument: " << subarg << std::endl;
                }
            }
        }
        else
        {
            std::cout << "Command not valid" << std::endl;
        }
    }
}