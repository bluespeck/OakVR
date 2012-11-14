#pragma once

#include <vector>
#include <string>

namespace ro3d
{
	// These functions are defined in the ro3d project in the Core solution
	extern bool ro3dInit( std::vector<std::string> cmdLine );
	extern bool ro3dUpdate();
	extern void ro3dExit();

	std::vector<std::string> ParseCommandLine(int argc, char **argv);
	std::vector<std::string> ParseCommandLine(const std::string& cmdLine);

} // end namespace ro3d

