#pragma once

#if defined(OAKVR_WINDOWS32) || defined(OAKVR_WINDOWS64)

#	include <GL/glew.h>
//#	include <GL/wglew.h>
#	include <GLFW/glfw3.h>

#elif defined(OAKVR_LINUX32) || defined(OAKVR_LINUX64)
#	include <GL/glew.h>
#	include <GL/glext.h>
#	include <GL/glfw.h>
#endif

#include <cstdint>

#include "Log/Log.h"

#ifndef OAKVR_RENDER_DEBUG

inline auto CheckOpenGLError(const char *file, int line, const char* glFuncName) -> void
{
	GLenum err = glGetError();
	while (err)
	{
		std::string error;
		switch (err)
		{
			case GL_INVALID_VALUE:          error = "GL_INVALID_VALUE";			break;
			case GL_INVALID_ENUM:           error = "GL_INVALID_ENUM";			break;
			case GL_INVALID_OPERATION:      error = "GL_INVALID_OPERATION";		break;
			case GL_STACK_OVERFLOW:			error = "GL_STACK_OVERFLOW";		break;
			case GL_STACK_UNDERFLOW:		error = "GL_STACK_UNDERFLOW";		break;
			case GL_OUT_OF_MEMORY:          error = "GL_OUT_OF_MEMORY";			break;
			case GL_INVALID_FRAMEBUFFER_OPERATION:	error = "GL_INVALID_FRAMEBUFFER_OPERATION";	break;
			default: error = "GL_UNKNOWN_ERROR"; break;
		}
		oakvr::Log::Warning("%s:%d : OpenGL error calling \"%s\" \"%s\"", file, line, glFuncName, error.c_str());
		err = glGetError();
	}
}

#	define CHECK_OPENGL_ERROR(file, line, glFuncName) CheckOpenGLError(file, line, glFuncName)

#else
#	define CHECK_OPENGL_ERROR(file, line, glFuncName)

#endif

namespace oakvr
{
	namespace render
	{
		// credit to Mircea for this nice piece of code ^^ http://pushcpp.blogspot.ro/2014/10/simple-opengl-error-checking.html
		// define glCallAndCheck with both a return type and without
		template<typename glFunction, typename... glFunctionParams>
		auto glCallAndCheck_indirect(const char *file, int line, const char* glFuncName, glFunction glFunc, glFunctionParams... params)->typename std::enable_if <
			std::is_same<void, decltype(glFunc(params...))>::value,
			decltype(glFunc(params...))
		> ::type
		{
			glFunc(std::forward<glFunctionParams>(params)...);
			CHECK_OPENGL_ERROR(file, line, glFuncName);
		}

		template<typename glFunction, typename... glFunctionParams>
		auto glCallAndCheck_indirect(const char *file, int line, const char* glFuncName, glFunction glFunc, glFunctionParams... params)->typename std::enable_if <
			!std::is_same<void, decltype(glFunc(params...))>::value,
			decltype(glFunc(params...))
		> ::type
		{
			auto result = glFunc(std::forward<glFunctionParams>(params)...);
			CHECK_OPENGL_ERROR(file, line, glFuncName);
			return result;
		}
	}
}

#define glCallAndCheck(glFunc, ...) glCallAndCheck_indirect(__FILE__, __LINE__, #glFunc, glFunc, __VA_ARGS__)
