#pragma once

#include <string>
#include <memory>
#include <functional>

#if defined(OAKVR_WINDOWS32) || defined(OAKVR_WINDOWS64)
#	include <Windows.h>
#endif

namespace oakvr
{
	namespace render
	{
		class RenderWindow
		{
		public:
			RenderWindow();
			RenderWindow( const std::string &title, int posX, int posY, unsigned int width, unsigned int height);
			RenderWindow(const RenderWindow &rw) = delete;
			//RenderWindow(RenderWindow &&rw) = default;
			RenderWindow& operator=(const RenderWindow &rw) = delete;
			~RenderWindow();
			
			auto Initialize() -> bool;
			auto IsOpen() -> bool;
			auto IsValid() -> bool; // true if it is backed by a valid render context
			auto Minimize() -> void;
			auto Maximize() -> void;
			auto RestoreSize() -> void;
			auto SwapBuffers() -> void;

			
			inline auto GetPositionX() const -> int { return m_posX; }
			inline auto GetPositionY() const -> int { return m_posY; }
			auto SetPosition(int x, int y) -> void;

			inline auto GetWidth() -> unsigned int;
			inline auto GetHeight() -> unsigned int;
			auto SetSize(unsigned int width, unsigned int height) -> void;

			auto SetWindowSizeCallback(void(*f)(void *, int, int)) -> void;
			auto SetWindowFocusCallback(void(*f)(void *, int)) -> void;
			auto SetWindowPositionCallback(void(*f)(void *, int, int)) -> void;

			auto GetTitle() const -> const std::string & { return m_title; }
			auto SetTitle(const std::string &title) -> void;

			uint64_t GetNativeHandle() { return m_nativeHandle; }

			inline auto HasFocus() const -> bool { return m_bHasFocus; }
			auto OnFocusChanged(bool focused) -> void { m_bHasFocus = focused; }

			auto OnPositionChanged(int x, int y) -> void { m_posX = x; m_posY = y; }

		private:

			enum WindowState
			{
				eWS_Normal,
				eWS_Minimized,
				eWS_Maximized
			};

			std::string m_title;
			int m_posX, m_posY;
			unsigned int m_width, m_height;
			WindowState m_windowState;
			
			uint64_t m_nativeHandle;

			class RenderWindowImpl;
			std::unique_ptr<RenderWindowImpl> m_pImpl;

			bool m_bFullScreen = false;
			bool m_bHasFocus = false;

#if defined(OAKVR_WINDOWS32) || defined(OAKVR_WINDOWS64)
			friend auto WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) -> LRESULT;
#endif

		};

		inline auto RenderWindow::GetWidth() -> unsigned int
		{
			return m_width;
		}

		inline auto RenderWindow::GetHeight() -> unsigned int
		{
			return m_height;
		}

	} // namespace render
} // namespace oakvr
