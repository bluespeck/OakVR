#pragma once

#include <memory>
#include <mutex>

namespace ro3d
{
	template<typename T>
	class Singleton
	{
	public:
		static std::shared_ptr<T> GetInstance()
		{
			static std::once_flag m_InstanceInitOnceFlag;
			static std::shared_ptr<T> m_pInstance;

			std::call_once(m_InstanceInitOnceFlag, [&]{ m_pInstance.reset(new T); });
			return std::shared_ptr(m_pInstance);
		}
			
	protected:
		Singleton(){}
		virtual ~Singleton(){}

	protected:

	};

}	// namespace ro3d
