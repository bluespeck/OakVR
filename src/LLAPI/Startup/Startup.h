#pragma once

#include <vector>
#include <string>

namespace ro3d
{
	// These functions are defined in the ro3d project in the Core solution
	extern bool Oak3DInit( std::vector<std::string> cmdLine );
	extern bool Oak3DUpdate();
	extern void Oak3DExit();

	std::vector<std::string> ParseCommandLine(int argc, char **argv);
	std::vector<std::string> ParseCommandLine(const std::string& cmdLine);

} // end namespace ro3d

