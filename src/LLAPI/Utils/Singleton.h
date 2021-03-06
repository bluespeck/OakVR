#pragma once

#include <memory>
#include <mutex>

namespace oakvr
{
	template<typename T>
	class Singleton
	{
	public:
		static T& GetInstance()
		{
			static T instance;
			return instance;
		}
		
	protected:
		Singleton(){}
		virtual ~Singleton(){}
		Singleton(const Singleton &);
		Singleton(Singleton &&);
		auto operator=(const Singleton &) -> void;
	};

}	// namespace oakvr
