
#include <cassert>
#include <algorithm>

#include "InterfaceFocusManager.h"
#include "Input/MouseInput.h"

namespace Oak3D
{
	namespace Leaf3D
	{
		// --------------------------------------------------------------------------------
		InterfaceFocusManager::InterfaceFocusManager()
		{

		}

		// --------------------------------------------------------------------------------
		void InterfaceFocusManager::RegisterFocusable(IFocusable *pFocusable)
		{
			m_focusables.push_back(pFocusable);
		}

		// --------------------------------------------------------------------------------
		void InterfaceFocusManager::UnregisterFocusable(IFocusable *pFocusable)
		{
			if(m_focusables.size() == 0)
				return;

			auto it = std::find(m_focusables.begin(), m_focusables.end(), pFocusable);
			assert(it != m_focusables.end());
			if(it != m_focusables.end())
				m_focusables.erase(it);
		}

		// --------------------------------------------------------------------------------
		void InterfaceFocusManager::Update()
		{
			auto mousePosition = Oak3D::Input::MouseInput::GetInstance()->GetPosition();
			IFocusable *pToGiveFocus = nullptr;
			uint32_t minDepth = (uint32_t) -1;

			for(auto it = m_focusables.begin(); it != m_focusables.end(); ++it)
			{
				(*it)->SetFocus(false);
				FocusZone focusZone = (*it)->GetFocusZone();
				if(focusZone.m_focusRect.m_pos.x <= mousePosition.first && focusZone.m_focusRect.m_pos.y <= mousePosition.second 
					&& focusZone.m_focusRect.m_pos.x + focusZone.m_focusRect.m_size.width >= mousePosition.first
					&& focusZone.m_focusRect.m_pos.y + focusZone.m_focusRect.m_size.height >= mousePosition.second
					&& focusZone.m_focusDepth < minDepth)
				{
					pToGiveFocus = *it;
					minDepth = focusZone.m_focusDepth;
				}
			}
			IFocusable *pHasMouseCaptured = GetMouseOwner();
			if(pHasMouseCaptured != nullptr)
			{
				pHasMouseCaptured->SetFocus(true);
				return;
			}

			if(pToGiveFocus)
				pToGiveFocus->SetFocus(true);
		}

		// --------------------------------------------------------------------------------
		IFocusable *InterfaceFocusManager::GetMouseOwner()
		{
			IFocusable * pFocusable = (IFocusable *)Oak3D::Input::MouseInput::GetInstance()->GetMouseOwner();
			if(m_focusables.size() > 0 && std::find(m_focusables.begin(), m_focusables.end(), pFocusable) != m_focusables.end())
				return pFocusable;

			return nullptr;
		}

		// --------------------------------------------------------------------------------
		IFocusable *InterfaceFocusManager::SetMouseOwner(IFocusable *pFocusable)
		{
			IFocusable *pOldFocusable = (IFocusable *)Oak3D::Input::MouseInput::GetInstance()->SetMouseOwner(pFocusable);
			if(m_focusables.size() > 0 && std::find(m_focusables.begin(), m_focusables.end(), pOldFocusable) != m_focusables.end())
				return pOldFocusable;
			return nullptr;
		}

	}
}
