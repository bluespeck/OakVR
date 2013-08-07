#include "Renderer/Renderer/RenderWindow.h"
#include "Log/Log.h"

#include <GL/glew.h>
#include <GL/glfw.h>


namespace oakvr
{
	namespace render
	{
		class RenderWindow::RenderWindowImpl
		{
			uint32_t osHandler;
		};

		// --------------------------------------------------------------------------------
		RenderWindow::RenderWindow() :
		m_pImpl{new RenderWindowImpl()}
		{
			m_windowState = eWS_Normal;
			m_bFullScreen = false;
			m_osHandle = 0;
			m_posX = m_posY = 0;
			m_width = 640;
			m_height = 480;
			m_title = "oakvr";

		}

		// --------------------------------------------------------------------------------
		RenderWindow::RenderWindow( const std::string &title, int posX, int posY, unsigned int width, unsigned int height)
			: m_title {title}, m_posX{posX}, m_posY{posY}, m_width{width}, m_height{height}, m_pImpl{new RenderWindowImpl()}
		{

		}

		// --------------------------------------------------------------------------------
		RenderWindow::~RenderWindow()
		{
			glfwCloseWindow();
		}

		// --------------------------------------------------------------------------------
		bool RenderWindow::Initialize()
		{
			if(glfwInit() == GL_FALSE)
			{
				Log::PrintError("Failed to initialize GLFW!\n");
				return false;
			}
			//glfwOpenWindowHint(GLFW_FSAA_SAMPLES, 4);
			//glfwOpenWindowHint(GLFW_OPENGL_VERSION_MAJOR, 3);
			//glfwOpenWindowHint(GLFW_OPENGL_VERSION_MINOR, 3);
			//glfwOpenWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
			//glfwOpenWindowHint(GLFW_OPENGL_PROFILE, 0);


			if(glfwOpenWindow(0, 0, 0, 0, 0, 0, 0, 0, GLFW_WINDOW) == GL_FALSE)
			{
				Log::PrintError("Failed to open a window !\n");
				glfwTerminate();
				return false;
			}
			else
			{
				Log::PrintInfo("RW Initialized!\n");
				return true;
			}
		}

		void RenderWindow::SwapBuffers()
		{
			glfwSwapBuffers();
		}

		// --------------------------------------------------------------------------------
		void RenderWindow::Minimize()
		{

		}

		// --------------------------------------------------------------------------------
		void RenderWindow::Maximize()
		{
		}

		// --------------------------------------------------------------------------------
		void RenderWindow::RestoreSize()
		{

		}

	} // namespace Render
} // namespace oakvr
