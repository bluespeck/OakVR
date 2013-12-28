Project "Time"
	kind "StaticLib"
	language "C++"

	includedirs{ ".." }
	
	files {"**.h", "Timer.cpp"}
	PlatformSpecificFiles("**_", ".cpp")
