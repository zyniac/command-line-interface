#include "Interpreter.h"
#include <iostream>

Argument Interpreter::getArgument(std::vector<std::string>& splits, std::vector<std::string>::iterator& itr)
{
	unsigned char status = 0;
	Argument::ArgumentData data;
	bool together = false;

	while (itr < splits.end())
	{
		if ((*itr).size() > 1 && (*itr)[0] == '-') // min -<1-char>		- 2
		{
			++status;
			if ((*itr).size() > 1 && status == 1) // min --<1-char>		- 3
			{
				if ((*itr)[1] == '-')
				{
					if ((*itr).size() > 2) // Written out arguments mustn't be case sensitive
					{
						data.status = Argument::ArgumentStatus::WRITTEN_OUT;
						data.argument = itr->substr(2);
						boost::algorithm::to_lower(data.argument);
					}
					else
					{
						data.status = Argument::ArgumentStatus::INVALID;
						break;
					}
				}
				else
				{
					data.status = Argument::ArgumentStatus::COMPACT;
					data.argument = itr->substr(1);
				}
			}
			else // Next Argument (Sub Argument Chain stops here), break
			{
				break;
			}
		}
		else
		{
			if (status == 1)
			{
				if (together)
				{
					if (itr->size() > 0 && (*(itr->end() - 1)) == '"')
					{
						if (itr->size() > 1 && (*(itr->end() - 2)) == '\\')
						{
							(*(data.subarguments.end() - 1)).append(' ' + *itr);
						}
						else
						{
							(*(data.subarguments.end() - 1)).append(' ' + itr->substr(0, itr->size() - 1));
							together = false;
						}
					}
					else
					{
						(*(data.subarguments.end() - 1)).append(' ' + *itr);
					}
				}
				else if ((*itr).size() > 0 && (*itr)[0] == '"')
				{
					if (itr->size() > 0 && (*(itr->end() - 1)) == '"')
					{
						data.subarguments.emplace_back(itr->substr(1, itr->size() - 2));
					}
					else
					{
						together = true;
						data.subarguments.emplace_back(itr->substr(1));
					}
				}
				else if ((*itr).size() > 0 && (*itr)[0] == '\\')
				{
					boost::algorithm::to_lower(*itr);
					data.subarguments.emplace_back(itr->substr(1));
				}
				else
				{
					boost::algorithm::to_lower(*itr);
					data.subarguments.emplace_back(*itr);
				}
			}
			else // Invalid, starts with subargument
			{
				data.status = Argument::ArgumentStatus::INVALID;
				break;
			}
		}

		++itr;
	}

	return Argument(data);
}

ArgumentList Interpreter::compileCommand(std::string command)
{
	std::vector<std::string> splits;
	boost::split(splits, command, boost::is_any_of(" "));
	std::string invoke = splits[0];
	boost::algorithm::to_lower(invoke);
	splits.erase(splits.begin());
	std::vector<std::string>::iterator itr = splits.begin();
	ArgumentList al(std::move(invoke));

	if (al.getInvoke().size() < CMD_MIN_LENGTH)
	{
		al.setInvalid();
		return al;
	}
	while (itr < splits.end())
	{
		Argument arg = Interpreter::getArgument(splits, itr);

		if (arg.getStatus() == Argument::ArgumentStatus::INVALID)
		{
			al.setInvalid();
			break;
		}

		al.push(std::move(arg));
	}
	return al;
}