#pragma once

#include <list>
#include <tchar.h>

class IComponent;

class CObject
{
public:
	CObject( void ); 	
	virtual ~CObject( void );
	
	void AddChild(CObject *pObj);
	void AddBrother(CObject *pObj);

	CObject *GetRootObj();

	void AddCustomComponent(IComponent *pComponent);
	void AddRenderComponent();
	void AddSoundComponent();

	float	IsObjectUnderMouse();
		
public:
	// links to other objects
	CObject *m_pParent;
	CObject *m_pChild;
	CObject *m_pBrother;

	unsigned int m_objID;

	// List of the components this object has
	std::list<IComponent *> m_lstComponents;

protected:
	static unsigned long m_objCount;
	
};