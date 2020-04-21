#pragma once

#include <cstdint>
#include <utility>

#include "Utils/Singleton.h"
#include "Utils/Types.h"

namespace oakvr::input
{
	class MouseInput : public oakvr::Singleton<MouseInput>
	{
	public:
		class MouseInputImpl;

		MouseInput();
		~MouseInput();
		auto Update() -> void;

		auto IsLeftButtonDown() const -> bool;
		auto IsMiddleButtonDown() const -> bool;
		auto IsRightButtonDown() const -> bool;
		auto IsLeftButtonUp() const -> bool;
		auto IsMiddleButtonUp() const -> bool;
		auto IsRightButtonUp() const -> bool;
		auto IsLeftButtonHeld() const -> bool;
		auto IsMiddleButtonHeld() const -> bool;
		auto IsRightButtonHeld() const -> bool;
		auto IsLeftButtonPressed() const -> bool;
		auto IsMiddleButtonPressed() const -> bool;
		auto IsRightButtonPressed() const -> bool;
		auto IsLeftButtonReleased() const -> bool;
		auto IsMiddleButtonReleased() const -> bool;
		auto IsRightButtonReleased() const -> bool;
		auto HasMouseMoved() const -> bool;

		auto GetPosition() const->std::pair<float, float>;
		auto GetPositionDelta() const->std::pair<float, float>;
		auto GetWheelDelta() const->int32_t;

		auto GetMouseOwner() -> void*;
		auto SetMouseOwner(void* newOwner) -> void*;

	private:
		up<MouseInputImpl> m_pImpl;
		void* m_pMouseOwner = nullptr;
	};
}
namespace oakvr::input::mouse
{
	inline auto Update() -> void { MouseInput::GetInstance().Update(); }
	inline auto IsLeftButtonDown()	-> bool { return MouseInput::GetInstance().IsLeftButtonDown(); }
	inline auto IsMiddleButtonDown() -> bool { return MouseInput::GetInstance().IsMiddleButtonDown(); }
	inline auto IsRightButtonDown()	-> bool	{ return MouseInput::GetInstance().IsRightButtonDown(); }
	inline auto IsLeftButtonUp() -> bool { return MouseInput::GetInstance().IsLeftButtonUp(); }
	inline auto IsMiddleButtonUp() -> bool { return MouseInput::GetInstance().IsMiddleButtonUp(); }
	inline auto IsRightButtonUp() -> bool { return MouseInput::GetInstance().IsRightButtonUp(); }
	inline auto IsLeftButtonHeld() -> bool { return MouseInput::GetInstance().IsLeftButtonHeld(); }
	inline auto IsMiddleButtonHeld() -> bool { return MouseInput::GetInstance().IsMiddleButtonHeld(); }
	inline auto IsRightButtonHeld() -> bool { return MouseInput::GetInstance().IsRightButtonHeld(); }
	inline auto IsLeftButtonPressed() -> bool { return MouseInput::GetInstance().IsLeftButtonPressed(); }
	inline auto IsMiddleButtonPressed() -> bool { return MouseInput::GetInstance().IsMiddleButtonPressed(); }
	inline auto IsRightButtonPressed() -> bool { return MouseInput::GetInstance().IsRightButtonPressed(); }
	inline auto IsLeftButtonReleased() -> bool { return MouseInput::GetInstance().IsLeftButtonReleased(); }
	inline auto IsMiddleButtonReleased() -> bool { return MouseInput::GetInstance().IsMiddleButtonReleased(); }
	inline auto IsRightButtonReleased() -> bool { return MouseInput::GetInstance().IsRightButtonReleased(); }
	inline auto HasMouseMoved() -> bool { return MouseInput::GetInstance().HasMouseMoved(); }

	inline auto GetPosition() -> std::pair<float, float> { return MouseInput::GetInstance().GetPosition(); }
	inline auto GetPositionDelta() -> std::pair<float, float> { return MouseInput::GetInstance().GetPositionDelta(); }

	inline auto GetWheelDelta() -> int32_t { return MouseInput::GetInstance().GetWheelDelta(); }

	inline void *GetMouseOwner() { return MouseInput::GetInstance().GetMouseOwner(); }
	inline void *SetMouseOwner(void *newOwner) { MouseInput::GetInstance().SetMouseOwner(newOwner); }
}
