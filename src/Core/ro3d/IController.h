
// --------------------------------------------------------------------------------

// --------------------------------------------------------------------------------

#ifndef __OAK3D_INCLUDE_CORE_ICONTROLLER_H__
#define __OAK3D_INCLUDE_CORE_ICONTROLLER_H__

namespace ro3d
{
	namespace Core
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
	} // namespace Core
}	// namespace ro3d

#endif
