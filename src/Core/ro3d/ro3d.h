
// --------------------------------------------------------------------------------

// --------------------------------------------------------------------------------

#ifndef __OAK3D_INCLUDE_OAK3D_H__
#define __OAK3D_INCLUDE_OAK3D_H__

#include "Oak3D/Engine.h"
#include "Utils/Singleton.h"

namespace Oak3D
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

	class Oak3D : public LLAPI::Singleton<Oak3D>
	{
	public:
		//friend class Core::Singleton<Oak3D>;
		void Update();
		OperatingSystem os;
		RenderingAPI renderAPI;
	
	protected:
		Oak3D();
		~Oak3D();

	private:
		Engine *m_pEngine;
	};
	
}	// namespace Oak3D

#endif
