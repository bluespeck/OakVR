#include <cstdio>
#include <vector>
#include <string>

#include "Startup.h"

int main(int argc, char **argv)
{
	if(!oakvr::oakvrInit(oakvr::ParseCommandLine(argc, argv)))
	{
		printf("Failed to initialize oakvr!!!\n");
	}
	else
	{
		printf("oakvr successfully initialized.\n");

		while(true)
		{
			if(!oakvr::oakvrUpdate())
				break;
		}

		oakvr::oakvrExit();
	}
	
	return 0;
}
