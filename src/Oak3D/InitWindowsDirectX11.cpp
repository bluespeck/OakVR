
// --------------------------------------------------------------------------------
// Written by      Mihai Tudorache 2011
// --------------------------------------------------------------------------------

#include "Oak3DInit.h"

#include "../Core/Windows/WindowsRenderWindow.h"
#include "../Core/Windows/DirectX/DirectX11/DirectX11GraphicsEngine.h"
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
	Core::GraphicsEngine *CreateGraphicsEngine()
	{
		return new Core::DirectX11GraphicsEngine();
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
