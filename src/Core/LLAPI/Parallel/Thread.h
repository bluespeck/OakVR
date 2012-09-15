
// --------------------------------------------------------------------------------
// --------------------------------------------------------------------------------

#ifndef __OAK3D_INCLUDE_CORE_THREAD_H__
#define __OAK3D_INCLUDE_CORE_THREAD_H__

#include <functional>
#include <cstdint>

namespace Oak3D
{
	namespace Core
	{
		class Thread
		{
		public:
			template<typename CallableFunction>
			Thread(CallableFunction func, void *pData);
			~Thread();
			
			void Join();
			void Sleep(uint64_t ms);
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
				ThreadFunc *pFunc = reinterpret_cast<ThreadFunc *>(pThis);
				// call the actual thread function
				pFunc->func(pFunc->arg);
				// and delete the ThreadFunc container created in the constructor
				delete pFunc;
				pFunc = nullptr;
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
			// Create ThreadFunc container here and delete it in ThreadStart
			ThreadFunc *pFunc = new ThreadFunc();
			pFunc->func = func;
			pFunc->arg = pData;
			CreateThread(ThreadStart, pFunc);
		}

		
	}
}

#endif
