ro3dProject "Log"
	kind "StaticLib"
	language "C++"

	includedirs{ ".." }
	
	files {"**.h"}
	ro3dPlatformSpecificFiles("**_", ".cpp")
