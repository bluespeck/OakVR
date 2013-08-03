
#ifndef __OAKVR_INCLUDE_LEAF3D_FOCUSMANAGER_H__
#define __OAKVR_INCLUDE_LEAF3D_FOCUSMANAGER_H__

#include <list>

#include "IFocusable.h"
#include "Core/Utils/Singleton.h"

namespace oakvr
{
	namespace Leaf3D
	{
		class InterfaceFocusManager : public oakvr::Core::Singleton<InterfaceFocusManager>
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
