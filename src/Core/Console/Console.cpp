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
		if (input::keyboard::IsPressed(input::Key::backtick_tilde))
		{
			if (m_bOnScreen == false)
			{
				m_bOnScreen = true;
				m_pConsoleVisual = std::make_unique<ConsoleVisual>();
			}
			else
			{
				m_bOnScreen = false;
				m_pConsoleVisual.reset();
			}
			return;
		}

		if (m_bOnScreen)
		{
			auto keys = input::keyboard::GetKeysPressed();
			if (keys.size())
			{
				int keyCode = input::keyboard::ToASCII(keys[0]);
				if (std::isprint(keyCode))
					m_currentCommand += static_cast<char>(keyCode);
				else if (keyCode == 0x0d)
					m_currentCommand = "";
			}
			oakvr::render::DrawText(m_currentCommand, math::Vector3(-400, -30, 5.1), 0xffdcdccc, "Fira Mono Regular", 5);
		}
	}


	OAKVR_REGISTER_UPDATABLE(Console)
}