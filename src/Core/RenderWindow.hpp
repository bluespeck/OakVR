
namespace Oak3D
{
	namespace Core
	{
		// --------------------------------------------------------------------------------
		inline void RenderWindow::SetOSHandle(long int handle)
		{
			m_osHandle = handle;
		}

		// --------------------------------------------------------------------------------
		inline long int RenderWindow::GetOSHandle()
		{
			return m_osHandle;
		}

		// --------------------------------------------------------------------------------
		inline void RenderWindow::SetPositionX(int posX)
		{
			m_posX = posX;
		}

		// --------------------------------------------------------------------------------
		inline int RenderWindow::GetPositionX()
		{
			return m_posX;
		}

		// --------------------------------------------------------------------------------
		inline void RenderWindow::SetPositionY(int posY)
		{
			m_posY = posY;
		}

		// --------------------------------------------------------------------------------
		inline int RenderWindow::GetPositionY()
		{
			return m_posY;
		}

		// --------------------------------------------------------------------------------
		inline void RenderWindow::SetWidth(unsigned int width)
		{
			m_width = width;
		}

		// --------------------------------------------------------------------------------
		inline unsigned int RenderWindow::GetWidth()
		{
			return m_width;
		}

		// --------------------------------------------------------------------------------
		inline void RenderWindow::SetHeight(unsigned int height)
		{
			m_height = height;
		}

		// --------------------------------------------------------------------------------
		inline unsigned int RenderWindow::GetHeight()
		{
			return m_height;
		}

	}	// namespace Core
}	// namespace Oak3D