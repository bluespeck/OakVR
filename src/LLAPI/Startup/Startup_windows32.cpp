#include "Startup.h"
#include "Log/Log.h"

#include <Windows.h>

#include <iostream>


BOOL WINAPI HandlerRoutine(_In_ DWORD dwCtrlType);

// --------------------------------------------------------------------------------
//int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
int main(int argc, char **argv)
{
	oakvr::Log::SetOutFilename("output.log");
	//oakvr::oakvr *oak3D = oakvr::oakvr::GetInstance();
	if(!oakvr::oakvrInit(oakvr::ParseCommandLine(argc, argv)))//std::string(lpCmdLine))))
	{
		oakvr::Log::PrintError("Failed to initialize OakVR!!!\n");
	}
	else
	{
		// Add our handler for the console window
		SetConsoleCtrlHandler(HandlerRoutine, TRUE);

		oakvr::Log::PrintInfo("OakVR successfully initialized.\n");

		// Enter the main loop
		MSG msg = {0};
		while(true)
		{
			// Check to see if any messages are waiting in the queue
			if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
			{
				TranslateMessage(&msg);

				if (msg.message == WM_QUIT)
					break;

				DispatchMessage(&msg);
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

BOOL WINAPI HandlerRoutine(_In_ DWORD dwCtrlType)
{
	if (dwCtrlType == CTRL_CLOSE_EVENT)
	{
		oakvr::oakvrExit();
	}
	return TRUE;
}
