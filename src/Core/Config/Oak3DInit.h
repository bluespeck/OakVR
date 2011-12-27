
// --------------------------------------------------------------------------------

// --------------------------------------------------------------------------------

#ifndef __OAK3D_INCLUDE_INITOAK3D_H__
#define __OAK3D_INCLUDE_INITOAK3D_H__

namespace Oak3D
{
	namespace Render
	{
		class RenderWindow;
		class GraphicsEngine;
	}

	namespace Core
	{
		class Timer;
	}

	Render::RenderWindow *CreateRenderWindow();
	Render::GraphicsEngine *CreateGraphicsEngine();
	Core::Timer *CreateTimer();
}	// namespace Oak3D

#endif
