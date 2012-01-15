#include <algorithm>

#include "IUpdatable.h"

namespace Oak3D
{
	namespace Core
	{
		std::list<IUpdatable *> *IUpdatable::s_updatableList = nullptr;
		bool IUpdatable::s_bDeleteListIfEmpty = false;

		IUpdatable::IUpdatable()
		{
			GetUpdatableList()->push_back(this);
		}

		IUpdatable::~IUpdatable()
		{
			// TODO will the equality be ok?
			GetUpdatableList()->erase(std::find(s_updatableList->begin(), s_updatableList->end(), this));
			if(s_bDeleteListIfEmpty && s_updatableList->size() == 0)
				delete s_updatableList;
		}

		void IUpdatable::Update(float dt)
		{

		}
	} // namespace Core
} // namespace Oak3D
