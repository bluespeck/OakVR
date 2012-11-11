#include <vector>
#include <string>
#include <regex>

#include "Startup.h"

namespace Oak3D
{
	std::vector<std::string> ParseCommandLine(int argc, char **argv)
	{
		std::vector<std::string> cmdLine;
		cmdLine.resize(argc);
		for(int i = 0; i < argc; ++i)
		{
			cmdLine.push_back(std::string(argv[i]));
		}
		return cmdLine;			
	}

	std::vector<std::string> ParseCommandLine(const std::string& args)
	{
		std::vector<std::string> cmdLine;
		std::sregex_token_iterator it(args.begin(), args.end(), std::regex("[ ]+"), -1);
		std::sregex_token_iterator end;
		for(; it != end; ++it)
		{
			cmdLine.push_back(it->str());
		}
		return cmdLine;
	}
}