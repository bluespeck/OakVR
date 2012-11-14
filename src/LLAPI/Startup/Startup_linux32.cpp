#include <cstdio>
#include <vector>
#include <string>

#include "Startup.h"

int main(int argc, char **argv)
{
	if(!ro3d::ro3dInit(ro3d::ParseCommandLine(argc, argv)))
	{
		printf("Failed to initialize ro3d!!!\n");
	}
	else
	{
		printf("ro3d successfully initialized.\n");

		while(true)
		{
			if(!ro3d::ro3dUpdate())
				break;
		}

		ro3d::ro3dExit();
	}
	
	return 0;
}
