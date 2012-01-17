
#ifndef __OAK3D_INCLUDE_INPUT_MOUSEINPUT_H__
#define __OAK3D_INCLUDE_INPUT_MOUSEINPUT_H__

#include <cstdint>
#include <utility>

#include "Core/Utils/Singleton.h"

namespace Oak3D
{
	namespace Input
	{
		class MouseInput : public Core::Singleton<MouseInput>
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
			int32_t GetWheelDelta();

			void *GetMouseOwner();
			void *SetMouseOwner(void *newOwner);

		private:
			MouseInputImpl *m_pImpl;
			void *m_pMouseOwner;
		};
	}
}

#endif
