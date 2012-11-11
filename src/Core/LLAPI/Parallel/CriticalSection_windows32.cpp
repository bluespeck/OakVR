
#if OAK3D_OS == OAK3D_OS_WINDOWS

#include <windows.h>

#include "CriticalSection.h"

namespace Oak3D
{
	namespace Core
	{
		struct CriticalSection::CriticalSectionImpl
		{
			CRITICAL_SECTION critSection;
		};

		CriticalSection::CriticalSection()
		{
			m_pImpl = new CriticalSectionImpl;
			InitializeCriticalSectionAndSpinCount(&m_pImpl->critSection, 0x00000400);
		}

		CriticalSection::~CriticalSection()
		{
			DeleteCriticalSection(&m_pImpl->critSection);
			delete m_pImpl;
		}

		void CriticalSection::EnterCriticalSection()
		{
			::EnterCriticalSection(&m_pImpl->critSection);
		}

		void CriticalSection::LeaveCriticalSection()
		{
			::LeaveCriticalSection(&m_pImpl->critSection);
		}
	}
}

#endif
