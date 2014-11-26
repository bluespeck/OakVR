#include "Console.h"

#include "OakVR/OakVR.h"
#include "Input/KeyboardInput/KeyboardInput.h"
#include "ConsoleVisual.h"
#include "Text/Text.h"


#include <memory>
#include <cctype>

namespace oakvr
{
	bool Console::Update(float dt)
	{
		HandleInput();

		return true;
	}

	void Console::HandleInput()
	{
		if (oakvr::render::RenderWindowHasFocus() && input::keyboard::IsPressed(input::Key::backtick_tilde))
		{
			if (m_bOnScreen == false)
			{
				m_bOnScreen = true;
				m_pConsoleVisual = std::make_unique<ConsoleVisual>();
				input::keyboard::Capture(this);
			}
			else
			{
				m_bOnScreen = false;
				m_pConsoleVisual.reset();
				input::keyboard::Release();
			}
			return;
		}

		if (m_bOnScreen)
		{
			if (oakvr::render::RenderWindowHasFocus())
			{
				auto keys = input::keyboard::GetKeysPressed();
				if (keys.size())
				{
					auto key = keys[0];
					int keyCode = input::keyboard::ToASCII(key);
					if (std::isprint(keyCode))
					{
						m_currentCommand.insert(m_cursorPosition++, 1, static_cast<char>(keyCode));

					}
					else if (key == input::Key::backspace && m_cursorPosition > 0)
					{
						m_currentCommand.erase(--m_cursorPosition, 1);
					}
					else if (key == input::Key::del && m_cursorPosition < m_currentCommand.length())
					{
						m_currentCommand.erase(m_cursorPosition, 1);
					}
					else if (key == input::Key::enter)
					{
						m_history.push_back(m_currentCommand);
						m_currentCommand.clear();
						m_cursorPosition = 0;
					}
					else if (key == input::Key::left && m_cursorPosition > 0)
					{
						--m_cursorPosition;
					}
					else if (key == input::Key::right && m_cursorPosition < m_currentCommand.length())
					{
						++m_cursorPosition;
					}
					else if (key == input::Key::home)
					{
						m_cursorPosition = 0;
					}
					else if (key == input::Key::end)
					{
						m_cursorPosition = m_currentCommand.length();
					}
				}
			}
			
			m_pConsoleVisual->DrawCommandline(m_currentCommand, m_cursorPosition);
			m_pConsoleVisual->DrawHistory(m_history);
			
		}
	}


	OAKVR_REGISTER_UPDATABLE(Console)
}