
	ro3dProject "DirectX9"
		platforms {"windows32", "windows64"}
		kind "StaticLib"
		language "C++"
		
		includedirs{ "../../.." }
		
		files { "**.h", "**.cpp" }