
#ifndef __OAK3D_INCLUDE_CORE_IUPDATABLE_H__
#define __OAK3D_INCLUDE_CORE_IUPDATABLE_H__

#include <list>

namespace ro3d
{
	namespace Core
	{
		class IUpdatable
		{
		public:

			IUpdatable();
			virtual ~IUpdatable();

			virtual void Update(float dt);

			static inline std::list<IUpdatable *>* GetUpdatableList();
			static inline void ReleaseUpdatableList();

		private:
			static std::list<IUpdatable *> *s_updatableList;
			static bool s_bDeleteListIfEmpty;
		};

		std::list<IUpdatable *>* IUpdatable::GetUpdatableList()
		{
			if(s_updatableList == nullptr)
				s_updatableList = new std::list<IUpdatable *>;
			return s_updatableList;
		}

		void IUpdatable::ReleaseUpdatableList()
		{
			if(s_updatableList != nullptr)
			{
				if(s_updatableList->size() == 0)
					delete s_updatableList;
				else
					s_bDeleteListIfEmpty = true;
			}
		}
	}
}


#endif
