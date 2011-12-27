
// --------------------------------------------------------------------------------

// --------------------------------------------------------------------------------

#ifndef __OAK3D_INCLUDE_SINGLETON_H__
#define __OAK3D_INCLUDE_SINGLETON_H__

namespace Oak3D
{
	namespace Core
	{

		template<typename T>
		class Singleton
		{
		public:
			static T* GetInstance()
			{
				if(m_pInstance)
					return m_pInstance;
				else
					return m_pInstance = new T;
			}
			
			static void Release()
			{
				if(m_pInstance)
					delete m_pInstance;
			}

		protected:
			Singleton(){}
			virtual ~Singleton(){}

		protected:
			static T* m_pInstance;
		};

		template<typename T>
		T *Singleton<T>::m_pInstance = nullptr;
	}
}	// namespace Oak3D
#endif
