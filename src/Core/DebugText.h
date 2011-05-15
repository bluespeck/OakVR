
// --------------------------------------------------------------------------------
// Written by      Mihai Tudorache 2011
// --------------------------------------------------------------------------------

#ifndef __OAK3D_INCLUDE_DEBUGTEXT_H__
#define __OAK3D_INCLUDE_DEBUGTEXT_H__

#include <string>
#include <cstdint>

namespace Oak3D
{
	namespace Core
	{
		class DebugText
		{
		public:
			virtual ~DebugText(){}
			virtual void Init() = 0;
			virtual void DrawText(const std::wstring &text, uint32_t x, uint32_t y) = 0;
		};
	}	// namespace Core
}	// namespace Oak3D

#endif
