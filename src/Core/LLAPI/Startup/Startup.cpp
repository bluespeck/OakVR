#include "Startup.h"

namespace Oak3D
{
	std::vector<std::string> ParseCommandLine(int argc, char **argv)
	{
		std::vector<std::string> cmdLine;
		for(int i = 0; i < argc; ++i)
		{
			cmdLine.push_back(std::string(argv[i]));
		}
		return cmdLine;			
	}
}