

#include "Object.h"

namespace Oak3D
{
	namespace Core
	{

		unsigned long Object::m_objCount = 0;

		// --------------------------------------------------------------------------------
		Object::Object( void )
		: m_objID( ++m_objCount )
		, m_pParent( nullptr )
		, m_pChild( nullptr )
		, m_pBrother( nullptr )
		{				
		}

		// --------------------------------------------------------------------------------
		Object::~Object( void )
		{
			m_pParent = nullptr;
			m_pChild = nullptr;
			m_pBrother = nullptr;

			for(auto it = m_lstControllers.begin(); it != m_lstControllers.end(); ++it)
			{
				delete *it;				
			}
		}

		// --------------------------------------------------------------------------------
		void Object::AddBrother(Object *pObj)
		{
			if(m_pBrother == nullptr)
			{
				m_pBrother = pObj;
			}
			else
			{
				Object *p = m_pBrother;
				while(p->m_pBrother != nullptr)
				{
					p = p->m_pBrother;
				}
				p->m_pBrother = pObj;
			}
			pObj->m_pParent = m_pParent;
		}

		// --------------------------------------------------------------------------------
		void Object::AddChild(Object *pObj)
		{
			if(m_pChild == nullptr)
			{
				// This object has no children. Add pObj as its only child
				m_pChild = pObj;		
			}
			else
			{
				// This object has children. Add pObj at the end of the children list
				Object *p = m_pChild;
				while(p->m_pBrother != nullptr)
				{
					p = p->m_pBrother;
				}
				p->m_pBrother = pObj;		
			}

			// Link child to its parent
			pObj->m_pParent = this;
		}
	} // namespace Core
}	// namespace Oak3D
