
// --------------------------------------------------------------------------------
// Written by      Mihai Tudorache 2011
// --------------------------------------------------------------------------------

#ifndef __OAK3D_INCLUDE_STRINGID_H__
#define __OAK3D_INCLUDE_STRINGID_H__

#include <string>
#include <cstdint>

namespace Oak3D
{
	namespace Utils
	{
		class StringId
		{
		public:
			StringId(uint32_t id);
			StringId(std::wstring strId);
			
			const std::wstring &GetStrId()
			{
				return m_strId;
			}

			uint32_t GetHashId()
			{
				return m_id;
			}


		private:
			std::wstring m_strId;
			uint32_t m_id;
		};
	}	// namespace Utils
}	// namespace Oak3D

#endif
