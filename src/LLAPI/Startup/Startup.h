#pragma once

#include <vector>
#include <string>

namespace oakvr
{
	// These functions are defined in the ro3d project in the Core solution
	extern bool oakvrInit( std::vector<std::string> cmdLine );
	extern bool oakvrUpdate();
	extern void oakvrExit();

	std::vector<std::string> ParseCommandLine(int argc, char **argv);
	std::vector<std::string> ParseCommandLine(const std::string& cmdLine);

} // end namespace ro3d

