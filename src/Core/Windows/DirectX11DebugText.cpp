
#include <string>
#include <fstream>
#include <cassert>
#include <cctype>

#include "DirectX11DebugText.h"
#include "../Font.h"

namespace Oak3D
{
	namespace Core
	{
		DirectX11DebugText::~DirectX11DebugText()
		{			
		}

		void DirectX11DebugText::Init()
		{
			m_pFont->Initialize(L"../resources/font/DebugFont.index", L"../resources/font/DebugFont.bmp");
		}

		void DirectX11DebugText::DrawText(const std::wstring &text, uint32_t x, uint32_t y)
		{
			Font::TextVertex *pVertices = m_pFont->BuildVertexArray(text, (float)x, (float)y);
			// TODO add text output
		}

	} // namespace Core
} // namespace Oak3D