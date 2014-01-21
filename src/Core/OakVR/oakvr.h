#pragma once

#include "OakVR/Engine.h"
#include "Utils/Singleton.h"

namespace oakvr
{
	class OakVR : public Singleton<OakVR>
	{
	public:
		friend bool oakvrUpdate();
		friend bool oakvrInit( std::vector<std::string> cmdLine );
		friend void oakvrExit();
		
		OakVR();
		virtual ~OakVR();
	private:
		
		Engine m_engine;
		
		bool Update();
	};
	
}	// namespace oakvr

