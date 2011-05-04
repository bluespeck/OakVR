
// --------------------------------------------------------------------------------
// Copyright      Mihai Tudorache 2011
// --------------------------------------------------------------------------------

#ifndef __OAK3D_INCLUDE_RENDERWINDOWWINDOWS_H__
#define __OAK3D_INCLUDE_RENDERWINDOWWINDOWS_H__

#ifdef OAK3D_WINDOWS

#include <string>
#include "../RenderWindow.h"

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

namespace Oak3D
{
	namespace Core
	{
		class WindowsRenderWindow : public RenderWindow
		{
		public:
			WindowsRenderWindow( HINSTANCE hInstance );
			WindowsRenderWindow( HINSTANCE hInstance, const std::wstring &title, int posX, int posY, unsigned int width, unsigned int height );

			// Overrides
			virtual void Initialize();
			virtual void Minimize();
			virtual void Maximize();
			virtual void RestoreSize();

			// Generic message handler			
			static LRESULT CALLBACK WndProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam );

		protected:
			HINSTANCE m_hInstance;
			LRESULT WindowsMessageHandler( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam );			
		};
	}
}

#endif

#endif
