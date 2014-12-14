#pragma once

#include "OakVR/Sprite.h"
#include <string>

namespace oakvr
{
	class ConsoleVisual
	{
	public:
		ConsoleVisual();

		auto DrawHistory(std::vector<std::string> vecHistory) -> void;
		auto DrawCommandline(std::string commandLine, size_t cursorPosition)->void;
	private:
		oakvr::render::Sprite m_historyBackground;
		oakvr::render::Sprite m_cmdLineBackground;
	};
}