
// --------------------------------------------------------------------------------
// --------------------------------------------------------------------------------

#ifndef __OAK3D_INCLUDE_CORE_THREAD_H__
#define __OAK3D_INCLUDE_CORE_THREAD_H__

#include <functional>

namespace Oak3D
{
	namespace Core
	{
		class Thread
		{
		public:
			template<typename CallableFunction>
			Thread(CallableFunction func, void *pData);
			
			void Join();
			static void Sleep(uint32_t ms);
		private:
			struct ThreadFunc
			{
				std::function<int(void *)> func;
				void *arg;
			};

			// --------------------------------------------------------------------------------
			// To be defined for each platform; this will be replaced at some point by std::thread
			void CreateThread(uint32_t (pThreadFunction)(void *), void *pData);

			// --------------------------------------------------------------------------------
			static uint32_t ThreadStart(void *pThis)
			{
				// call the actual thread function
				ThreadFunc *pFunc = reinterpret_cast<ThreadFunc *>(pThis);
				pFunc->func(pFunc->arg);
				delete pFunc;
				return 0;
			}

		private:
			struct ThreadImpl;
			ThreadImpl *m_pImpl;
		};

		// --------------------------------------------------------------------------------
		template<typename CF>
		Thread::Thread(CF func, void *pData)
		{
			ThreadFunc *pFunc = new ThreadFunc();
			pFunc->func = func;
			pFunc->arg = pData;
			CreateThread(ThreadStart, pFunc);
		}

		
	}
}

#endif
