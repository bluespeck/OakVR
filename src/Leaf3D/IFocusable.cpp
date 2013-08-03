
#include "IFocusable.h"
#include "InterfaceFocusManager.h"

namespace oakvr
{
	namespace Leaf3D
	{
		// --------------------------------------------------------------------------------
		IFocusable::IFocusable()
		: m_bHasFocus(false)
		{
			InterfaceFocusManager::GetInstance()->RegisterFocusable(this);
		}

		// --------------------------------------------------------------------------------
		IFocusable::~IFocusable()
		{
			InterfaceFocusManager::GetInstance()->UnregisterFocusable(this);
		}

		// --------------------------------------------------------------------------------
		void IFocusable::SetFocus(bool focus)
		{
			m_bHasFocus = focus;
		}

		// --------------------------------------------------------------------------------
		bool IFocusable::IsFocused()
		{
			return m_bHasFocus;
		}
		
		// --------------------------------------------------------------------------------
		IFocusable* IFocusable::CaptureMouse()
		{
			return InterfaceFocusManager::GetInstance()->SetMouseOwner(this);
		}

		// --------------------------------------------------------------------------------
		IFocusable *IFocusable::ReleaseMouse()
		{
			return InterfaceFocusManager::GetInstance()->SetMouseOwner(nullptr);
		}

		// --------------------------------------------------------------------------------
		bool IFocusable::HasCapturedMouse()
		{
			return InterfaceFocusManager::GetInstance()->GetMouseOwner() == this;
		}

	}
}