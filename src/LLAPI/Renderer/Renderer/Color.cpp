#include "Color.h"

namespace oakvr
{
	namespace render
	{
		const Color	Color::Black(0xff000000);
		const Color Color::Red(0xff0000ff);
		const Color Color::Green(0xff00ff00);
		const Color Color::Blue(0xff0000ff);
		const Color Color::Yellow(0xffffff00);
		const Color Color::Cyan(0xff00ffff);
		const Color Color::Magenta(0xffff00ff);
		const Color Color::White(0xffffffff);

		Color::Color()
		:r(0.0f), g(0.0f), b(0.0f), a(1.0f)
		{
		}

		Color::Color(uint32_t color)
		{
			const float f = 1.0f / 255.0f;
			r = f * (float) (uint8_t) (color >> 16);
			g = f * (float) (uint8_t) (color >>  8);
			b = f * (float) (uint8_t) (color >>  0);
			a = f * (float) (uint8_t) (color >> 24);
		}
	}
}
