
	Project "DirectX9Renderer"
		removeplatforms { "linux*" }
		kind "StaticLib"
		language "C++"
		
		includedirs{ "../../.." }
		
		files { "**.h", "**.cpp" }
