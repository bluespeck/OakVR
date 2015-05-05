#include <vector>
#include <string>
#include <regex>

#include "Startup.h"

namespace oakvr
{
	auto ParseCommandLine(int argc, char **argv) -> std::vector<std::string>
	{
		std::vector<std::string> cmdLine;
		cmdLine.resize(argc);
		for(int i = 0; i < argc; ++i)
		{
			cmdLine.push_back(std::string(argv[i]));
		}
		return cmdLine;			
	}

	auto ParseCommandLine(const std::string& args) -> std::vector<std::string>
	{
		std::vector<std::string> cmdLine;

		// this is deleted in newer vs versions
		/*
		std::sregex_token_iterator it(args.begin(), args.end(), std::regex("[ ]+"), -1);
		std::sregex_token_iterator end;
		for(; it != end; ++it)
		{
			cmdLine.push_back(it->str());
		}
		*/
		std::string acc;
		for (auto e : args)
		{
			if (e == ' ' || e == '\t')
			{
				if (acc.length() > 0)
				{
					cmdLine.push_back(acc);
					acc.clear();
				}
				else
					continue;
			}
			else
				acc.append(1, e);
		}

		return cmdLine;
	}
}
