#ifdef __Startup_h__
#	define __Startup_h__

#	include <vector>
#	include <string>

// These functions are defined in the Oak3D project in the Core solution
extern bool Oak3D::Oak3DInit( std::vector<std::string> cmdLine );
extern void Oak3D::Oak3DMainLoop();
extern void Oak3D::Oak3DExit();

namespace Oak3D
{
	vector<string> ParseCommandLine(int argc, char **argv);
}

#endif
