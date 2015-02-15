#pragma once

#include <vector>
#include <string>

namespace oakvr
{
	// These functions are defined in the oakvr project in the Core solution
	extern auto oakvrInit(std::vector<std::string> cmdLine) -> bool;
	extern auto oakvrUpdate() -> bool;
	extern auto oakvrExit() -> void;

	auto ParseCommandLine(int argc, char **argv) -> std::vector < std::string > ;
	auto ParseCommandLine(const std::string& cmdLine) -> std::vector < std::string > ;

} // end namespace oakvr

