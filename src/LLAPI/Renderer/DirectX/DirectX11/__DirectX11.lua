
	Project "DirectX11Renderer"
		removeplatforms { "linux*" }
		kind "StaticLib"
		language "C++"
		
		includedirs{ "../../.." }
		
		files { "**.h", "**.cpp" }
