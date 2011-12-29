
// --------------------------------------------------------------------------------

// --------------------------------------------------------------------------------

#ifndef __OAK3D_INCLUDE_OBJECT_H__
#define __OAK3D_INCLUDE_OBJECT_H__

#include <list>

#include "Core/Utils/StringID.h"

namespace Oak3D
{
	namespace Render
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

			Oak3D::Core::StringId m_objID;

			// Controllers running on this object
			std::list<IController *> m_lstControllers;

		protected:
			static unsigned long m_objCount;

		};
	} // namespace Render
} // namespace Oak3D

#endif
