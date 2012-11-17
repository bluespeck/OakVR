
#include <mutex>

#include "CriticalSection.h"

namespace ro3d
{
	namespace Core
	{
		struct CriticalSection::CriticalSectionImpl
		{
			std::mutex critSection;
		};

		CriticalSection::CriticalSection()
		{
			m_pImpl = new CriticalSectionImpl;
		}

		CriticalSection::~CriticalSection()
		{
			delete m_pImpl;
		}

		void CriticalSection::EnterCriticalSection()
		{
			m_pImpl->critSection.lock();
		}

		void CriticalSection::LeaveCriticalSection()
		{
			m_pImpl->critSection.unlock();
		}
	}
}

