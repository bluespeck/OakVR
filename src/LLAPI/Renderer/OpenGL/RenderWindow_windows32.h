#pragma once

#include <string>
#include "Renderer/IRenderer/RenderWindow.h"

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

namespace oakvr
{
	namespace render
	{
		class WindowsRenderWindow : public RenderWindow
		{
		public:
			WindowsRenderWindow();
			WindowsRenderWindow( const std::string &title, int posX, int posY, unsigned int width, unsigned int height );

			// Overrides
			virtual void Initialize();
			virtual void Minimize();
			virtual void Maximize();
			virtual void RestoreSize();
			virtual void Refresh(){};
			
			// Generic message handler			
			static LRESULT CALLBACK WndProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam );

		protected:
			LRESULT WindowsMessageHandler( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam );			
		};
	} // namespace Render
} // namespace oakvr
