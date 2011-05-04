
// --------------------------------------------------------------------------------
// Copyright      Mihai Tudorache 2011
// --------------------------------------------------------------------------------

#ifndef __OAK3D_INCLUDE_DIRECTXGRAPHICSENGINE_H__
#define __OAK3D_INCLUDE_DIRECTXGRAPHICSENGINE_H__

#if defined(OAK3D_WINDOWS) && defined(OAK3D_DIRECTX_11)

#include <windows.h>
#include <windowsx.h>
#include <d3d11.h>
#include <d3dx11.h>
#include <d3dx10.h>

// include the Direct3D Library file
#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "d3dx11.lib")
#pragma comment (lib, "d3dx10.lib")

#include "../GraphicsEngine.h"


namespace Oak3D
{
	namespace Core
	{
		class DirectX11GraphicsEngine : public GraphicsEngine
		{
		public:
			// constructors
			DirectX11GraphicsEngine();

			// overrides
			virtual void Initialize();
			virtual void Update( float dt );
			virtual void Render();
			virtual void Cleanup();
			

		private:
			IDXGISwapChain *m_pSwapChain;             // the swap chain interface
			ID3D11Device *m_pDevice;                     // Direct3D device interface
			ID3D11DeviceContext *m_pDeviceContext;           // Direct3D device context

			ID3D11RenderTargetView *m_pBackBufferRenderTargetView;
		};
	}
}

#endif

#endif
