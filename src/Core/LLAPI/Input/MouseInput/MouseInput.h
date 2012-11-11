#pragma once

#include <cstdint>
#include <utility>

#include "Utils/Singleton.h"

namespace Oak3D
{
	namespace Input
	{
		class MouseInput : public Oak3D::LLAPI::Singleton<MouseInput>
		{
		public:
			class MouseInputImpl;

			MouseInput();
			~MouseInput();
			void Update();

			bool IsLeftButtonDown();
			bool IsMiddleButtonDown();
			bool IsRightButtonDown();
			bool IsLeftButtonUp();
			bool IsMiddleButtonUp();
			bool IsRightButtonUp();
			bool IsLeftButtonHeld();
			bool IsMiddleButtonHeld();
			bool IsRightButtonHeld();
			bool IsLeftButtonPressed();
			bool IsMiddleButtonPressed();
			bool IsRightButtonPressed();
			bool IsLeftButtonReleased();
			bool IsMiddleButtonReleased();
			bool IsRightButtonReleased();
			bool HasMouseMoved();

			std::pair<int32_t, int32_t> GetPosition();
			std::pair<int32_t, int32_t> GetPositionDelta();
			int32_t GetWheelDelta();

			void *GetMouseOwner();
			void *SetMouseOwner(void *newOwner);

		private:
			MouseInputImpl *m_pImpl;
			void *m_pMouseOwner;
		};
	}
}
