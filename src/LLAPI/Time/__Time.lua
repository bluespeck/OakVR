Project "Time"
	kind "StaticLib"
	language "C++"
	ProjectGlobalConfig()
	
	includedirs{ ".." }
	
	files {"**.h", "Timer.cpp"}
	PlatformSpecificFiles("**_", ".cpp")
