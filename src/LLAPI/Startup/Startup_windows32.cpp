#include <Windows.h>

#include "Startup.h"

// --------------------------------------------------------------------------------
//int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
int main(int argc, char **argv)
{

	//oakvr::oakvr *oak3D = oakvr::oakvr::GetInstance();
	if(!oakvr::oakvrInit(oakvr::ParseCommandLine(argc, argv)))//std::string(lpCmdLine))))
	{
		printf("Failed to initialize oakvr!!!\n");
	}
	else
	{
		printf("OakVR successfully initialized.\n");
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
				if(!oakvr::oakvrUpdate())
					break;
			}
		}

		oakvr::oakvrExit();
	}
	return 0;
}
