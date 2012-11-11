ro3dProject "Time"
	kind "StaticLib"
	language "C++"

	includedirs{ ".." }
	
	files {"**.h"}
	ro3dPlatformSpecificFiles("**_", ".cpp")
