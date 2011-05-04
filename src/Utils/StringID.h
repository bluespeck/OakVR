
// --------------------------------------------------------------------------------
// Copyright      Mihai Tudorache 2011
// --------------------------------------------------------------------------------

#ifndef __OAK3D_INCLUDE_STRINGID_H__
#define __OAK3D_INCLUDE_STRINGID_H__

#include <string>
#include <cstdint>

namespace Oak3D
{
	namespace Utils
	{
		class StringID
		{
		public:
			StringID(uint32_t id);
			StringID(std::wstring strID);
			
			std::wstring &GetStrID()
			{
				return m_strId;
			}

			uint32_t GetID()
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
