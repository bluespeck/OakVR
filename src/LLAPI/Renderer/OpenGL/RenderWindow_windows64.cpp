
#include "Common.h"

#include "Renderer/Renderer/RenderWindow.h"
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
			m_osHandle = 0;
			m_posX = m_posY = 0;
			m_width = 1024;
			m_height = 768;
			m_title = "oakvr";

		}
		
		// --------------------------------------------------------------------------------
		RenderWindow::RenderWindow(const std::string &title, int posX, int posY, unsigned int width, unsigned int height)
			: m_title{ title }, m_posX{ posX }, m_posY{ posY }, m_width{ width }, m_height{ height }, m_pImpl{ new RenderWindowImpl() }
		{

		}

		// --------------------------------------------------------------------------------
		RenderWindow::~RenderWindow()
		{
			glfwDestroyWindow(m_pImpl->m_pWindow);
		}

		// --------------------------------------------------------------------------------
		bool RenderWindow::Initialize()
		{
			// Initialize GLFW
			if (!glfwInit())
			{
				Log::PrintError("Failed to initialize GLFW!\n");
				return false;
			}

			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
			glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
			glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

			if (!(m_pImpl->m_pWindow = glfwCreateWindow(m_width, m_height, m_title.c_str(), nullptr, nullptr)))
			{
				Log::PrintError("Failed to open a window !\n");
				glfwTerminate();
				return false;
			}
			glfwSetWindowPos(m_pImpl->m_pWindow, m_posX, m_posY);
			glfwMakeContextCurrent(m_pImpl->m_pWindow);
			glfwSetWindowCloseCallback(m_pImpl->m_pWindow, OnCloseWindow);
			return true;
		}

		bool RenderWindow::IsOpen()
		{
			return glfwGetWindowAttrib(m_pImpl->m_pWindow, GLFW_VISIBLE);
		}

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

	} // namespace render
} // namespace oakvr
