#include "ConsoleVisual.h"
#include "Math/Vector3.h"
#include "Text/Text.h"

namespace oakvr
{
	ConsoleVisual::ConsoleVisual()
		: m_historyBackground("Console_HistoryBackground_Sprite", math::Vector3(0, 300, 5), 800, 600, "Console_BG"),
		m_cmdLineBackground("Console_CommandLineBackground_Sprite", math::Vector3(0, -30, 5), 800, 50, "Console_BG")
	{
	}

	auto ConsoleVisual::DrawHistory(std::vector<std::string> vecHistory) -> void
	{
		long int maxLines = static_cast<long int>(vecHistory.size());
		if (maxLines > 30)
			maxLines = 30;
		int lineIndex = 0;
		for (long int i = static_cast<long int>(vecHistory.size()) - 1; i >= static_cast<long int>(vecHistory.size() - maxLines); --i, lineIndex++)
		{
			static float verticalSize = render::GetGlyphHeight(' ', "Fira Mono Regular", 5);
			oakvr::render::DrawText(vecHistory[i], math::Vector3(-400, 5 + lineIndex * verticalSize, 5.2f), 0xffdcdccc, "Fira Mono Regular", 5);
		}
	}

	auto ConsoleVisual::DrawCommandline(std::string commandLine, size_t cursorPosition)->void
	{
		static float spaceSize = render::GetGlyphWidth(' ', "Fira Mono Regular", 5);
		oakvr::render::DrawText(commandLine, math::Vector3(-400, -30, 5.2f), 0xffdcdccc, "Fira Mono Regular", 5);
		oakvr::render::DrawText("_", math::Vector3(-400 + cursorPosition * spaceSize, -31, 5.4f), 0xffdcdccc, "Fira Mono Regular", 5);
	}

}