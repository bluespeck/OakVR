
// --------------------------------------------------------------------------------
// Written by      Mihai Tudorache 2011
// --------------------------------------------------------------------------------

#ifndef __OAK3D_INCLUDE_INITOAK3D_H__
#define __OAK3D_INCLUDE_INITOAK3D_H__

namespace Oak3D
{
	namespace Core
	{
		class RenderWindow;
		class GraphicsEngine;
		class Timer;
		class ThreadFactory;
	}

	Core::RenderWindow *CreateRenderWindow();
	Core::GraphicsEngine *CreateGraphicsEngine();
	Core::Timer *CreateTimer();
	Core::ThreadFactory *CreateThreadFactory();
}	// namespace Oak3D

#endif
