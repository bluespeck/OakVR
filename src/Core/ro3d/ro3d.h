#pragma once

#include "ro3d/Engine.h"
#include "Utils/Singleton.h"

namespace ro3d
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

	class ro3d : public Singleton<ro3d>
	{
	public:
		OperatingSystem os;
		RenderingAPI renderAPI;
		
		friend bool ro3dUpdate();
		friend bool ro3dInit( std::vector<std::string> cmdLine );
		friend void ro3dExit();
		
		ro3d();
		virtual ~ro3d();
	protected:
		
		ro3d(const ro3d &);
		Engine &m_sEngine;
		
		void Update();
	};
	
}	// namespace ro3d

