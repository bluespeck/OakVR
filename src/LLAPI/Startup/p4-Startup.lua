Project "Startup"
	kind "StaticLib"
	language "C++"

	includedirs{ ".." }
	
	files {"*.h"}
	PlatformSpecificFiles("**", ".cpp")

	files {"Startup.cpp"}
