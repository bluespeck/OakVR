
#include "ro3d/WindowsRenderWindow.h"
#include "Time/WindowsTimer.h"


namespace ro3d
{
	// --------------------------------------------------------------------------------
	Render::RenderWindow *CreateRenderWindow()
	{
		return new ro3d::Render::WindowsRenderWindow();
	}

} // namespace ro3d
