#include <cstdio>
#include <vector>
#include <string>

#include "Startup.h"

int main(int argc, char **argv)
{
	if(!ro3d::Oak3DInit(ro3d::ParseCommandLine(argc, argv)))
	{
		printf("Failed to initialize ro3d!!!\n");
	}
	else
	{
		printf("ro3d successfully initialized.\n");

		while(true)
		{
			if(!ro3d::Oak3DUpdate())
				break;
		}

		ro3d::Oak3DExit();
	}
	
	return 0;
}
