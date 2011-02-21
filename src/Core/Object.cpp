

#include "Object.h"

unsigned long CObject::m_objCount = 0;

CObject::CObject( void ):
m_pParent( NULL ), 
m_pChild( NULL ), 
m_pBrother( NULL )
{	
	m_objCount++;
	m_objID = m_objCount;
}

CObject::~CObject( void )
{
	m_pParent = NULL;
	m_pChild = NULL;
	m_pBrother = NULL;

	std::list<IComponent *>::iterator it = m_lstComponents.begin();
	while(it != m_lstComponents.end())
	{
		delete *it;
		++it;
	}
}

void CObject::AddBrother(CObject *pObj)
{
	if(m_pBrother == NULL)
	{
		m_pBrother = pObj;
	}
	else
	{
		CObject *p = m_pBrother;
		while(p->m_pBrother != NULL)
		{
			p = p->m_pBrother;
		}
		p->m_pBrother = pObj;
	}
	pObj->m_pParent = m_pParent;
}

void CObject::AddChild(CObject *pObj)
{
	if(m_pChild == NULL)
	{
		// This object has no children. Add pObj as its only child
		m_pChild = pObj;		
	}
	else
	{
		// This object has children. Add pObj at the end of the children list
		CObject *p = m_pChild;
		while(p->m_pBrother != NULL)
		{
			p = p->m_pBrother;
		}
		p->m_pBrother = pObj;		
	}
	
	// Link child to its parent
	pObj->m_pParent = this;
}

void CObject::AddRenderComponent()
{
	m_lstComponents.push_back(new CRenderComponent(this));
}

void CObject::AddCustomComponent(IComponent *pComponent)
{
	m_lstComponents.push_back(pComponent);
}

float CObject::IsObjectUnderMouse()
{
	return CEngine::GetRenderEngine()->IsObjectUnderMouse( this ); 
}