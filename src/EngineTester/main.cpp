
#include <Windows.h>

#define OAK3D_WINDOWS
#define OAK3D_DIRECTX_11

#include "../Oak3D/Oak3D.h"

// --------------------------------------------------------------------------------
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{

	Oak3D::Oak3D *oak3D = Oak3D::Oak3D::GetInstance(hInstance);
		
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