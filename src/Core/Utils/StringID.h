
// --------------------------------------------------------------------------------
// --------------------------------------------------------------------------------

#ifndef __OAK3D_INCLUDE_STRINGID_H__
#define __OAK3D_INCLUDE_STRINGID_H__

#include <string>
#include <cstdint>

namespace Oak3D
{
	namespace Core
	{
		class StringId
		{
		public:
			StringId(uint32_t id);
			StringId(const std::string &strId);
			StringId(const char *strId);
			
			void SetStrId(const std::string &strId);
			bool operator ==(const StringId &id);

			// --------------------------------------------------------------------------------
			const std::string &GetStrId() const
			{
				return m_strId;
			}
			
			// --------------------------------------------------------------------------------
			uint32_t GetHashId() const
			{
				return m_id;
			}


		private:
			std::string m_strId;
			uint32_t m_id;
		};
	}	// namespace Core
}	// namespace Oak3D

#endif
