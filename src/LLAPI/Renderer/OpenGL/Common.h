#pragma once

#include <cstdint>

#if defined(OAKVR_WINDOWS32) || defined(OAKVR_WINDOWS64)

#	include <GL/glew.h>
//#	include <GL/wglew.h>
#	include <GLFW/glfw3.h>

#elif defined(OAKVR_LINUX32) || defined(OAKVR_LINUX64)
#	include <GL/glext.h>
#	include <GL/glew.h>
#	include <GL/glfw.h>
#endif
