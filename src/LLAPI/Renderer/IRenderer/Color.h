#pragma once

#include <cstdint>

namespace oakvr
{
	namespace Render
	{
		struct Color
		{
			float r;
			float g;
			float b;
			float a;
			
			Color();
			Color(uint32_t color);
			Color(float r, float g, float b, float a);

			operator uint32_t () const;
			operator float const * () const;
			operator float * ();

			static const Color Black;
			static const Color White;
			static const Color Red;
			static const Color Blue;
			static const Color Green;
			static const Color Magenta;
			static const Color Cyan;
			static const Color Yellow;
		};

		inline Color::operator uint32_t () const
		{
			uint32_t rr =	(uint32_t) (r * 255.0f);
			uint32_t gg =	(uint32_t) (g * 255.0f);
			uint32_t bb	=	(uint32_t) (b * 255.0f);
			uint32_t aa	=	(uint32_t) (a * 255.0f);

			return (aa << 24) | (rr << 16) | (gg << 8) | bb;
		}

		inline Color::operator float * ()
		{
			return (float *)&r;
		}

		inline Color::operator const float * () const
		{
			return (float *)&r;
		}

	}
}
