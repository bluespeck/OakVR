
// --------------------------------------------------------------------------------
// Written by      Mihai Tudorache 2011
// --------------------------------------------------------------------------------

#ifndef __OAK3D_INCLUDE_DIRECTXUTILS_H__
#define __OAK3D_INCLUDE_DIRECTXUTILS_H__

#if defined(DEBUG) || defined(_DEBUG)
	#include <sstream>
	#include <dxerr.h>
	#pragma comment (lib, "dxerr.lib")

	#ifndef HR
	#define HR(x)\
	{\
		HRESULT hr = (x);\
		if(FAILED(hr))\
		{\
			DXTrace(__FILE__, (unsigned long int)__LINE__, hr, L#x, true );\
		}\
	}
	#endif
	
	#ifndef HR_ERR
	#define HR_ERR(x, pErrorMsg)\
	{\
		HRESULT hr = (x);\
		if(FAILED(hr))\
		{\
			MessageBoxA(0, (char*)(pErrorMsg->GetBufferPointer()), "Error...", MB_OK);\
			pErrorMsg->Release();\
			pErrorMsg = nullptr;\
		}\
	}
	#endif
#else
	#ifndef HR
	#define HR(x) (x)
	#endif
	
	#ifndef HR_ERR
	#define HR_ERR(x,y) (x)
	#endif
#endif

	
#endif
