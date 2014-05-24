#pragma once

#include <cstdint>
#include <utility>

#include "Utils/Singleton.h"

namespace oakvr
{
	namespace input
	{
		class MouseInput : public oakvr::Singleton<MouseInput>
		{
		public:
			class MouseInputImpl;

			MouseInput();
			~MouseInput();
			void Update();

			bool IsLeftButtonDown() const;
			bool IsMiddleButtonDown() const;
			bool IsRightButtonDown() const;
			bool IsLeftButtonUp() const;
			bool IsMiddleButtonUp() const;
			bool IsRightButtonUp() const;
			bool IsLeftButtonHeld() const;
			bool IsMiddleButtonHeld() const;
			bool IsRightButtonHeld() const;
			bool IsLeftButtonPressed() const;
			bool IsMiddleButtonPressed() const;
			bool IsRightButtonPressed() const;
			bool IsLeftButtonReleased() const;
			bool IsMiddleButtonReleased() const;
			bool IsRightButtonReleased() const;
			bool HasMouseMoved() const;

			std::pair<int32_t, int32_t> GetPosition() const;
			std::pair<int32_t, int32_t> GetPositionDelta() const;
			int32_t GetWheelDelta() const;

			void *GetMouseOwner();
			void *SetMouseOwner(void *newOwner);

		private:
			MouseInputImpl *m_pImpl;
			void *m_pMouseOwner;
		};
	}
}
