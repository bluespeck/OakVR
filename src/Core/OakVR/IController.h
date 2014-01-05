#pragma once

namespace oakvr
{
	namespace core
	{
		class IController
		{
		public:
			IController( class Object * ) { m_pObj = nullptr; }
			virtual ~IController() { }
			virtual void DeleteMe();

			virtual	void Update( float dt ) { };

			class CObject *m_pObj;	// Points to the object on which this controller is placed
		};
	} // namespace core
}	// namespace oakvr
