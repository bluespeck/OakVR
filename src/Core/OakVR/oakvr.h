#pragma once

#include "OakVR/Engine.h"
#include "Utils/Singleton.h"

namespace oakvr
{
	class OakVR : public Singleton<OakVR>
	{
		friend class Singleton < OakVR > ;
		friend bool oakvrUpdate();
		friend bool oakvrInit(std::vector<std::string> cmdLine);
		friend void oakvrExit();
	public:
		void CleanupEngine();
	private:
		OakVR();
		~OakVR();
		
		Engine m_engine;
		
		bool Update();
	};
	
}	// namespace oakvr

