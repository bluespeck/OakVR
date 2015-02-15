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
#if defined(_WIN32)
		std::sregex_token_iterator it(args.begin(), args.end(), std::regex("[ ]+"), -1);
		std::sregex_token_iterator end;
		for(; it != end; ++it)
		{
			cmdLine.push_back(it->str());
		}
#else
		for(int i = 0, start = 0; i < args.size(); ++i)
		{
			if(args[i] == ' ')
			{
				cmdLine.push_back(args.substr(start, i-start));
				start = i+1;
			}
		}
#endif

		return cmdLine;
	}
}
