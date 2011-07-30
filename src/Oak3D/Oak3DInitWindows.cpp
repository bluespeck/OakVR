
// --------------------------------------------------------------------------------
// Written by      Mihai Tudorache 2011
// --------------------------------------------------------------------------------

#include "Oak3DConfig.h"

#if OAK3D_OS == OAK3D_OS_WINDOWS

#include "Oak3DInit.h"
#include "../Core/Windows/WindowsRenderWindow.h"
#include "../Core/Windows/WindowsTimer.h"
#include "../Core/Windows/WindowsThreadFactory.h"

namespace Oak3D
{
	// --------------------------------------------------------------------------------
	Core::RenderWindow *CreateRenderWindow()
	{
		return new Core::WindowsRenderWindow();
	}
	
	// --------------------------------------------------------------------------------
	Core::Timer *CreateTimer()
	{
		return new Core::WindowsTimer();
	}

	// --------------------------------------------------------------------------------
	Core::ThreadFactory *CreateThreadFactory()
	{
		return new Core::WindowsThreadFactory();
	}
}

#endif // OAK3D_OS_WINDOWS