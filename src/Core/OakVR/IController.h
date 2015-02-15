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
			virtual auto DeleteMe() -> void;

			virtual	auto Update( float dt )  -> void{ };

			class CObject *m_pObj;	// Points to the object on which this controller is placed
		};
	} // namespace core
}	// namespace oakvr
