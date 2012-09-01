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
		Oak3D::Oak3DMainLoop();
		Oak3D::Oak3DExit();
	}
	
	return 0;
}