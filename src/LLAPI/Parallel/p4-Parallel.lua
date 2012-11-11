ro3dProject "Parallel"
	kind "StaticLib"
	language "C++"

	files {"**.h"}
	ro3dPlatformSpecificFiles("**_", ".cpp")
