
// --------------------------------------------------------------------------------

// --------------------------------------------------------------------------------

#ifndef __OAKVR_INCLUDE_CORE_INITOAKVR_H__
#define __OAKVR_INCLUDE_CORE_INITOAKVR_H__

namespace oakvr
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
}	// namespace oakvr

#endif
