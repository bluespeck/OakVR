ro3dProject "Time"
	kind "StaticLib"
	language "C++"

	includedirs{ ".." }
	
	files {"**.h", "Timer.cpp"}
	ro3dPlatformSpecificFiles("**_", ".cpp")
