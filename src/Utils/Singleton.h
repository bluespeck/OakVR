
// --------------------------------------------------------------------------------
// Copyright      Mihai Tudorache 2011
// --------------------------------------------------------------------------------

#ifndef __OAK3D_INCLUDE_SINGLETON_H__
#define __OAK3D_INCLUDE_SINGLETON_H__

namespace Oak3D
{
	namespace Utils
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

			static T* GetInstance(void *param)
			{
				m_param = param;
				if(m_pInstance)
					return m_pInstance;
				else
					return m_pInstance = new T();
			}

			static void Release()
			{
				if(m_pInstance)
					delete m_pInstance;
			}
		protected:
			Singleton();

		protected:
			static T* m_pInstance;
			static void *m_param;
		};

		template<typename T>
		T *Singleton<T>::m_pInstance = nullptr;
		template<typename T>
		void *Singleton<T>::m_param = nullptr;
	}
}	// namespace Oak3D
#endif
