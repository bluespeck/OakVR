#include "Core/Config/OAk3DConfig.h"

#if OAK3D_OS == OAK3D_OS_WINDOWS

#include <Windows.h>

#include "Oak3D.h"

// --------------------------------------------------------------------------------
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{

	Oak3D::Oak3D *oak3D = Oak3D::Oak3D::GetInstance();
	
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
			oak3D->Update();
		}
	}

	oak3D->Release();

	return 0;
}

#endif
