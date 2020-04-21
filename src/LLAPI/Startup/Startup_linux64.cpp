#include "Startup.h"
#include "Log/Log.h"

#include <cstdio>
#include <vector>
#include <string>



int main(int argc, char **argv)
{
	if(!oakvr::oakvrInit(oakvr::ParseCommandLine(argc, argv)))
	{
		oakvr::Log::PrintError("Failed to initialize OakVR!!!\n");
	}
	else
	{
		oakvr::Log::PrintInfo("OakVR successfully initialized.\n");

		while(true)
		{
			if(!oakvr::oakvrUpdate())
				break;
		}

		oakvr::oakvrExit();
	}
	
	return 0;
}
