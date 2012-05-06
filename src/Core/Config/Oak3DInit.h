
// --------------------------------------------------------------------------------

// --------------------------------------------------------------------------------

#ifndef __OAK3D_INCLUDE_CORE_INITOAK3D_H__
#define __OAK3D_INCLUDE_CORE_INITOAK3D_H__

namespace Oak3D
{
	namespace Render
	{
		class RenderWindow;
		class IRenderer;
	}

	namespace Core
	{
		class Timer;
	}

	Render::RenderWindow *CreateRenderWindow();
	Render::IRenderer *CreateRenderer();
	Core::Timer *CreateTimer();
}	// namespace Oak3D

#endif
