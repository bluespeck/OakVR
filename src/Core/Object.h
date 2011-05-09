
// --------------------------------------------------------------------------------
// Written by      Mihai Tudorache 2011
// --------------------------------------------------------------------------------

#ifndef __OAK3D_INCLUDE_OBJECT_H__
#define __OAK3D_INCLUDE_OBJECT_H__

#include <list>
#include "../Utils/StringID.h"

namespace Oak3D
{
	namespace Core
	{

		class IController;

		class Object
		{
		public:
			Object( void ); 	
			virtual ~Object( void );

			void AddChild(Object *pObj);
			void AddBrother(Object *pObj);

			Object *GetRootObj();
			
		public:
			// links to other objects
			Object *m_pParent;
			Object *m_pChild;
			Object *m_pBrother;

			Oak3D::Utils::StringId m_objID;

			// Controllers running on this object
			std::list<IController *> m_lstControllers;

		protected:
			static unsigned long m_objCount;

		};
	} // namespace Core
}

#endif
