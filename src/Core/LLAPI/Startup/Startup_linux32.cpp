#include <cstdio>
#include <vector>
#include <string>

#include "Startup.h"

int main(int argc, char **argv)
{
	if(!Oak3D::Oak3DInit(Oak3D::ParseCommandLine(argc, argv)))
	{
		printf("Failed to initialize Oak3D!!!\n");
	}
	else
	{
		printf("Oak3D successfully initialized.\n");

		while(true)
		{
			if(!Oak3D::Oak3DUpdate())
				break;
		}

		Oak3D::Oak3DExit();
	}
	
	return 0;
}
