#ifndef __OAK3D_INCLUDE_CRITICALSECTION_H__
#define __OAK3D_INCLUDE_CRITICALSECTION_H__

namespace Oak3D
{
	namespace Core
	{
		class CriticalSection
		{
		public:
			CriticalSection();
			~CriticalSection();
			void EnterCriticalSection();
			void LeaveCriticalSection();

		private:
			struct CriticalSectionImpl;

			CriticalSectionImpl *m_pImpl;
		};

		class AutoLockCriticalSection
		{
		public:
			AutoLockCriticalSection(CriticalSection &critSection) : m_critSection(critSection) { m_critSection.EnterCriticalSection(); }
			~AutoLockCriticalSection() { m_critSection.LeaveCriticalSection(); }
		private:
			CriticalSection &m_critSection;
		};
	}
}


#endif
