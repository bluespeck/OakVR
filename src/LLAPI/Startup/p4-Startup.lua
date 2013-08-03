Project "Startup"
	kind "StaticLib"
	language "C++"

	includedirs{ ".." }
	
	files {"*.h", "Startup.cpp"}
	PlatformSpecificFiles("**", ".cpp")
	
