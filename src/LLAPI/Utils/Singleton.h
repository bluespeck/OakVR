#pragma once

namespace ro3d
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
			m_pInstance = nullptr;
		}

	protected:
		Singleton(){}
		virtual ~Singleton(){}

	protected:
		static T* m_pInstance;
	};

	template<typename T>
	T *Singleton<T>::m_pInstance = nullptr;
}	// namespace ro3d
