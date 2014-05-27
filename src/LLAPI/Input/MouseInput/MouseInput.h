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

		namespace mouse
		{
			inline void Update()			{ MouseInput::GetInstance().Update(); }
			inline bool IsLeftButtonDown()	{ return MouseInput::GetInstance().IsLeftButtonDown(); }
			inline bool IsMiddleButtonDown() { return MouseInput::GetInstance().IsMiddleButtonDown(); }
			inline bool IsRightButtonDown()		{ return MouseInput::GetInstance().IsRightButtonDown(); }
			inline bool IsLeftButtonUp()		{ return MouseInput::GetInstance().IsLeftButtonUp(); }
			inline bool IsMiddleButtonUp()		{ return MouseInput::GetInstance().IsMiddleButtonUp(); }
			inline bool IsRightButtonUp()		{ return MouseInput::GetInstance().IsRightButtonUp(); }
			inline bool IsLeftButtonHeld()		{ return MouseInput::GetInstance().IsLeftButtonHeld(); }
			inline bool IsMiddleButtonHeld()	{ return MouseInput::GetInstance().IsMiddleButtonHeld(); }
			inline bool IsRightButtonHeld()		{ return MouseInput::GetInstance().IsRightButtonHeld(); }
			inline bool IsLeftButtonPressed()	{ return MouseInput::GetInstance().IsLeftButtonPressed(); }
			inline bool IsMiddleButtonPressed() { return MouseInput::GetInstance().IsMiddleButtonPressed(); }
			inline bool IsRightButtonPressed()	{ return MouseInput::GetInstance().IsRightButtonPressed(); }
			inline bool IsLeftButtonReleased()	{ return MouseInput::GetInstance().IsLeftButtonReleased(); }
			inline bool IsMiddleButtonReleased(){ return MouseInput::GetInstance().IsMiddleButtonReleased(); }
			inline bool IsRightButtonReleased() { return MouseInput::GetInstance().IsRightButtonReleased(); }
			inline bool HasMouseMoved()			{ return MouseInput::GetInstance().HasMouseMoved(); }

			inline std::pair<int32_t, int32_t> GetPosition() { return MouseInput::GetInstance().GetPosition(); }
			inline std::pair<int32_t, int32_t> GetPositionDelta() { return MouseInput::GetInstance().GetPositionDelta(); }

			inline int32_t GetWheelDelta() { return MouseInput::GetInstance().GetWheelDelta(); }

			inline void *GetMouseOwner() { return MouseInput::GetInstance().GetMouseOwner(); }
			inline void *SetMouseOwner(void *newOwner) { MouseInput::GetInstance().SetMouseOwner(newOwner); }
		}
	}
}
