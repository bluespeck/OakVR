#include "MeshConverter.h"

#include <vector>
#include <string>
int main(const int argc, char **argv)
{
#if defined(OAKVR_WINDOWS64) || defined(OAKVR_WINDOWS32)
	int startIndex = 1;
#else
	int startIndex = 0;
#endif
	if (argc > startIndex)
	{
		std::vector<std::string> params;
		for (int i = startIndex; i < argc; ++i)
			params.emplace_back(argv[i]);
		
		oakvr::tools::MeshConverter mc;
		mc.ParseCommandLine(params);

	}
	
	return 0;
}