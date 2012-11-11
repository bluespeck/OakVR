
// --------------------------------------------------------------------------------
// --------------------------------------------------------------------------------

#ifndef __OAK3D_INCLUDE_CORE_UNIQUEID_H__
#define __OAK3D_INCLUDE_CORE_UNIQUEID_H__

namespace ro3d
{
	namespace Core
	{
		class UniqueId
		{
		public:
			UniqueId() m_id(s_currentId) {}
			uint32_t Get() { return m_id; }
		private:
			static uint32_t s_currentId;
			uint32_t m_id;
		};
	}
}

#endif
