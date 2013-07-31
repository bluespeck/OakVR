
#include "OakVR/WindowsRenderWindow.h"
//#include "Time/WindowsTimer.h"


namespace oakvr
{
	// --------------------------------------------------------------------------------
	Render::RenderWindow *CreateRenderWindow()
	{
		return new oakvr::Render::WindowsRenderWindow();
	}

} // namespace oakvr
