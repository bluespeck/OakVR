#pragma once

#include "OakVR/Engine.h"
#include "Utils/Singleton.h"

namespace oakvr
{
	enum OperatingSystem
	{
		eOS_Windows = 0,
		eOS_WindowsXP = eOS_Windows,
		eOS_WindowsVista = eOS_Windows,
		eOS_Windows7 = eOS_Windows
	};

	enum RenderingAPI
	{
		eRAPI_DirectX = 0,
		eRAPI_DirectX_9 = eRAPI_DirectX + 1,
		eRAPI_DirectX_10 = eRAPI_DirectX + 2,
		eRAPI_DIRECTX_11 = eRAPI_DirectX + 3
	};

	class oakvr : public Singleton<oakvr>
	{
	public:
		OperatingSystem os;
		RenderingAPI renderAPI;
		
		friend bool oakvrUpdate();
		friend bool oakvrInit( std::vector<std::string> cmdLine );
		friend void oakvrExit();
		
		oakvr();
		virtual ~oakvr();
	protected:
		
		oakvr(const oakvr &);
		Engine &m_sEngine;
		
		bool Update();
	};
	
}	// namespace oakvr

