
// --------------------------------------------------------------------------------

// --------------------------------------------------------------------------------

#ifndef __OAK3D_INCLUDE_CORE_INITOAK3D_H__
#define __OAK3D_INCLUDE_CORE_INITOAK3D_H__

namespace ro3d
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
}	// namespace ro3d

#endif
