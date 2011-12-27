
// --------------------------------------------------------------------------------
// --------------------------------------------------------------------------------

#ifndef __OAK3D_INCLUDE_THREAD_H__
#define __OAK3D_INCLUDE_THREAD_H__


namespace Oak3D
{
	namespace Core
	{
		class Thread
		{
		public:
			Thread(uint32_t (pThreadFunction)(void *), void *pData);
			static void Sleep(uint32_t ms);
		private:
			struct ThreadImpl;
			ThreadImpl *m_pImpl;
		};
	}
}

#endif
