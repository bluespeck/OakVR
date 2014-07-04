#include "MeshConverter.h"

#include <regex>
#include <algorithm>
#include <iterator>
#include <iostream>

#include "Dae2Oak.h"

namespace oakvr
{
	namespace tools
	{
		void MeshConverter::ParseCommandLine(std::vector<std::string> &params)
		{
			if (params[0] == "dae2oakvr")
			{
				oakvr::tools::Dae2Oakvr(params[1], params[2]);
			}
		}
	}
}