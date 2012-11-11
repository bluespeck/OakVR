#include <Windows.h>

#include "Startup.h"

// --------------------------------------------------------------------------------
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{

	//Oak3D::Oak3D *oak3D = Oak3D::Oak3D::GetInstance();
	if(!Oak3D::Oak3DInit(Oak3D::ParseCommandLine(std::string(lpCmdLine))))
	{
		printf("Failed to initialize Oak3D!!!\n");
	}
	else
	{
		printf("Oak3D successfully initialized.\n");
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
				Oak3D::Oak3DUpdate();
			}
		}

		Oak3D::Oak3DExit();
	}
	return 0;
}
