Project "Startup"
	kind "StaticLib"
	language "C++"
	ProjectGlobalConfig()
	
	includedirs{ ".." }
	
	files {"*.h", "Startup.cpp"}
	PlatformSpecificFiles("**", ".cpp")
	
