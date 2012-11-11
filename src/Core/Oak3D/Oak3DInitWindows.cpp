
#include "Oak3D/WindowsRenderWindow.h"
#include "Time/WindowsTimer.h"


namespace Oak3D
{
	// --------------------------------------------------------------------------------
	Render::RenderWindow *CreateRenderWindow()
	{
		return new Oak3D::Render::WindowsRenderWindow();
	}

} // namespace Oak3D
