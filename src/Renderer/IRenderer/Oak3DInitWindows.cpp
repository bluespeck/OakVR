
// --------------------------------------------------------------------------------
// --------------------------------------------------------------------------------

#include "Core/Config/Oak3DConfig.h"

#if OAK3D_OS == OAK3D_OS_WINDOWS

#include "Core/Config/Oak3DInit.h"
#include "Renderer/IRenderer/WindowsRenderWindow.h"
#include "Core/Time/WindowsTimer.h"
#include "Core/Parallel/ThreadFactory.h"

namespace Oak3D
{
	// --------------------------------------------------------------------------------
	Render::RenderWindow *CreateRenderWindow()
	{
		return new Oak3D::Render::WindowsRenderWindow();
	}

} // namespace Oak3D

#endif // OAK3D_OS_WINDOWS