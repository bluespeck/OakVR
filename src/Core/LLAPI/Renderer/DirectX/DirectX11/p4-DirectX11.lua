
	project "DirectX11"
		platforms {"native", "windows32", "windows64"}
		kind "StaticLib"
		language "C++"
		
		files { "**.h", "**.cpp" }
