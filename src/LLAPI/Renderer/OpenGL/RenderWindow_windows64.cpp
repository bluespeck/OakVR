
#include "Common.h"

#include "Renderer/Renderer/RenderWindow.h"
#include "Renderer/Renderer/Renderer.h"
#include "Log/Log.h"

namespace oakvr
{
	namespace render
	{
		void OnCloseWindow(GLFWwindow *pWindow)
		{
			glfwHideWindow(pWindow);
		}

		class RenderWindow::RenderWindowImpl
		{
		public:
			GLFWwindow *m_pWindow;
		};

		// --------------------------------------------------------------------------------
		RenderWindow::RenderWindow() :
			m_pImpl{ new RenderWindowImpl() }
		{
			m_windowState = eWS_Normal;
			m_bFullScreen = false;
			m_nativeHandle = 0;
			m_posX = m_posY = 0;
			m_width = 1024;
			m_height = 768;
			m_title = "oakvr";

		}
		
		// --------------------------------------------------------------------------------
		RenderWindow::RenderWindow(const std::string &title, int posX, int posY, unsigned int width, unsigned int height)
			: m_title( title ), m_posX{ posX }, m_posY{ posY }, m_width{ width }, m_height{ height }, m_pImpl{ new RenderWindowImpl() }
		{

		}

		// --------------------------------------------------------------------------------
		RenderWindow::~RenderWindow()
		{
			glfwDestroyWindow(m_pImpl->m_pWindow);
			// Terminate GLFW
			glfwTerminate();
		}

		// --------------------------------------------------------------------------------
		auto RenderWindow::Initialize() -> bool
		{
			// Initialize GLFW
			if (!glfwInit())
			{
				Log::Error("Failed to initialize GLFW!\n");
				return false;
			}

			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
			glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
			glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
			glfwSwapInterval(0);

			if (!(m_pImpl->m_pWindow = glfwCreateWindow(m_width, m_height, m_title.c_str(), nullptr, nullptr)))
			{
				Log::Error("Failed to open a window ! Most likely cause \"GLFW: Window creation will fail if the Microsoft GDI software OpenGL implementation is the only one available\"\n");
				glfwTerminate();
				return false;
			}
			m_bHasFocus = true;

			m_nativeHandle = reinterpret_cast<decltype(m_nativeHandle)>(m_pImpl->m_pWindow);	// watch out in the future! pointer to int conversion
			glfwSetWindowPos(m_pImpl->m_pWindow, m_posX, m_posY);
			glfwMakeContextCurrent(m_pImpl->m_pWindow);
			glfwSetWindowCloseCallback(m_pImpl->m_pWindow, OnCloseWindow);

			CHECK_OPENGL_ERROR;
			return true;
		}

		// --------------------------------------------------------------------------------
		auto RenderWindow::IsOpen() -> bool
		{
			return !!glfwGetWindowAttrib(m_pImpl->m_pWindow, GLFW_VISIBLE);
		}

		// --------------------------------------------------------------------------------
		auto RenderWindow::IsValid() -> bool
		{	
			return glfwGetCurrentContext() != nullptr;
		}

		// --------------------------------------------------------------------------------
		void RenderWindow::SwapBuffers()
		{
			glfwSwapBuffers(m_pImpl->m_pWindow);
		}

		// --------------------------------------------------------------------------------
		void RenderWindow::Minimize()
		{
			glfwIconifyWindow(m_pImpl->m_pWindow);
		}

		// --------------------------------------------------------------------------------
		void RenderWindow::Maximize()
		{
			// ??
		}

		// --------------------------------------------------------------------------------
		void RenderWindow::RestoreSize()
		{
			glfwRestoreWindow(m_pImpl->m_pWindow);
		}

		// --------------------------------------------------------------------------------
		void RenderWindow::SetSize(unsigned int width, unsigned int height)
		{
			m_width = width;
			m_height = height;
			glfwSetWindowSize(m_pImpl->m_pWindow, m_width, m_height);
		}

		// --------------------------------------------------------------------------------
		void RenderWindow::SetWindowSizeCallback(void (*pCallback)(void *, int, int))
		{
			glfwSetWindowSizeCallback(m_pImpl->m_pWindow, (void(*)(struct GLFWwindow *, int, int))pCallback);
		}

		// --------------------------------------------------------------------------------
		void RenderWindow::SetWindowFocusCallback(void(*pCallback)(void *, int))
		{
			glfwSetWindowFocusCallback(m_pImpl->m_pWindow, (void(*)(struct GLFWwindow *, int))pCallback);
		}

		// --------------------------------------------------------------------------------
		void RenderWindow::SetWindowPositionCallback(void(*pCallback)(void *, int, int))
		{
			glfwSetWindowPosCallback(m_pImpl->m_pWindow, (void(*)(struct GLFWwindow *, int, int))pCallback);
		}

		// --------------------------------------------------------------------------------
		void RenderWindow::SetPosition(int x, int y)
		{
			m_posX = x;
			m_posY = y;
			glfwSetWindowPos(m_pImpl->m_pWindow, m_posX, m_posY);
		}

		// --------------------------------------------------------------------------------
		void RenderWindow::SetTitle(const std::string &title)
		{
			m_title = title;
			glfwSetWindowTitle(m_pImpl->m_pWindow, m_title.c_str());
		}

	} // namespace render
} // namespace oakvr
