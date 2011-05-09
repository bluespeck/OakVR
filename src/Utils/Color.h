
// --------------------------------------------------------------------------------
// Written by      Mihai Tudorache 2011
// --------------------------------------------------------------------------------

#ifndef __OAK3D_INCLUDE_COLOR_H__
#define __OAK3D_INCLUDE_COLOR_H__

namespace Oak3D
{
	namespace Utils
	{

		struct Color
		{
			float RedAsFloat() { return (argb & 0xff0000 >> 16) * inv255; }
			float GreenAsFloat() { return (argb & 0xff00 >> 8) * inv255; }
			float BlueAsFloat() { return (argb & 0xff ) * inv255; }	
			float AlphaAsFloat() { return (argb & 0xff000000 >> 24) * inv255; }

			unsigned char RedAsByte() { return (unsigned char)(argb & 0xff0000 >> 16); }
			unsigned char GreenAsByte() { return (unsigned char)(argb & 0xff00 >> 8); }
			unsigned char BlueAsByte() { return (unsigned char)(argb & 0xff ); }
			unsigned char AlphaAsByte() { return (unsigned char)(argb & 0xff000000 >> 24); }

			unsigned long argb;
		private:
			static const float inv255;
		};

		const float Color::inv255 = 1.0f / 255.0f;
	} // namespace Utils
}

#endif
