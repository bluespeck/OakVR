Project "Log"
	kind "StaticLib"
	language "C++"
	ProjectGlobalConfig()
	
	includedirs{ ".." }
	
	files {"**.h", "Log.cpp"}
	PlatformSpecificFiles("**_", ".cpp")
