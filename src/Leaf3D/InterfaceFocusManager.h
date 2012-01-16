
#ifndef __OAK3D_INCLUDE_LEAF3D_FOCUSMANAGER_H__
#define __OAK3D_INCLUDE_LEAF3D_FOCUSMANAGER_H__

#include <list>

#include "IFocusable.h"
#include "Core/Utils/Singleton.h"

namespace Oak3D
{
	namespace Leaf3D
	{
		class InterfaceFocusManager : public Oak3D::Core::Singleton<InterfaceFocusManager>
		{
		public:
			InterfaceFocusManager();
			
			void RegisterFocusable(IFocusable *pFocusable);
			void UnregisterFocusable(IFocusable *pFocusable);
			void Update();

			IFocusable *GetMouseOwner();
			IFocusable *SetMouseOwner(IFocusable *pFocusable);
		private:
			std::list<IFocusable *> m_focusables;
		};
	}
}


#endif
