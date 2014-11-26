#include "ConsoleVisual.h"
#include "Math/Vector3.h"

namespace oakvr
{
	ConsoleVisual::ConsoleVisual()
		: m_historyBackground("Console_HistoryBackground_Sprite", math::Vector3(0, 300, 5), 800, 600, "Console_BG"),
		m_cmdLineBackground("Console_CommandLineBackground_Sprite", math::Vector3(0, -30, 5), 800, 50, "Console_BG")
	{
	}
}