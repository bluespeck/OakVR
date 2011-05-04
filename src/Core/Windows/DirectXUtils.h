
// --------------------------------------------------------------------------------
// Copyright      Mihai Tudorache 2011
// --------------------------------------------------------------------------------

#ifndef __OAK3D_INCLUDE_DIRECTXUTILS_H__
#define __OAK3D_INCLUDE_DIRECTXUTILS_H__

#if defined(DEBUG) || defined(_DEBUG)
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
#else
	#ifndef HR
	#define HR(x) (x)
	#endif
#endif

#endif
