#pragma once

#include "ArgumentList.h"
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/algorithm.hpp>
#include <vector>

namespace Interpreter
{
	Argument getArgument(std::vector<std::string>& splits, std::vector<std::string>::iterator& itr);
	ArgumentList compileCommand(std::string command);
}