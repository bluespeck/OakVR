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

	class ro3d : public LLAPI::Singleton<ro3d>
	{
	public:
		//friend class Core::Singleton<ro3d>;
		void Update();
		OperatingSystem os;
		RenderingAPI renderAPI;
	
	protected:
		ro3d();
		~ro3d();

	private:
		Engine *m_pEngine;
	};
	
}	// namespace ro3d

