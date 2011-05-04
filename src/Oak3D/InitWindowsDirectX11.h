
// --------------------------------------------------------------------------------
// Copyright      Mihai Tudorache 2011
// --------------------------------------------------------------------------------

#ifndef __OAK3D_INCLUDE_INITWINDOWSDIRECTX11_H__
#define __OAK3D_INCLUDE_INITWINDOWSDIRECTX11_H__

#if defined(OAK3D_WINDOWS) && defined(OAK3D_DIRECTX_11)

#include "../Core/Windows/WindowsRenderWindow.h"
#include "../Core/Windows/DirectX11GraphicsEngine.h"
#include "../Core/Windows/WindowsTimer.h"

namespace Oak3D
{
	Core::RenderWindow *CreateRenderWindow(HINSTANCE hInstance)
	{
		return new Core::WindowsRenderWindow(hInstance);
	}

	Core::GraphicsEngine *CreateGraphicsEngine()
	{
		return new Core::DirectX11GraphicsEngine();
	}

	Core::Timer *CreateTimer()
	{
		return new Core::WindowsTimer();
	}
}

#endif

#endif
