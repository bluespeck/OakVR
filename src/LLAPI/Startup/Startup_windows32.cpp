#include <Windows.h>

#include "Startup.h"

// --------------------------------------------------------------------------------
//int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
int main(int argc, char **argv)
{

	//ro3d::ro3d *oak3D = ro3d::ro3d::GetInstance();
	if(!ro3d::Oak3DInit(ro3d::ParseCommandLine(argc, argv)))//std::string(lpCmdLine))))
	{
		printf("Failed to initialize ro3d!!!\n");
	}
	else
	{
		printf("ro3d successfully initialized.\n");
		// Enter the main loop
		MSG msg = {0};
		while(true)
		{
			// Check to see if any messages are waiting in the queue
			if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);

				if(msg.message == WM_QUIT)
					break;
			}
			else
			{
				// engine update
				ro3d::Oak3DUpdate();
			}
		}

		ro3d::Oak3DExit();
	}
	return 0;
}
