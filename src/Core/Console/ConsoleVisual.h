#pragma once

#include "OakVR/Sprite.h"

namespace oakvr
{
	class ConsoleVisual
	{
	public:
		ConsoleVisual();
	private:
		oakvr::render::Sprite m_historyBackground;
		oakvr::render::Sprite m_cmdLineBackground;
	};
}