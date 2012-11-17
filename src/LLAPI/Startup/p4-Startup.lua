ro3dProject "Startup"
	kind "StaticLib"
	language "C++"

	includedirs{ ".." }
	
	files {"*.h"}
	ro3dPlatformSpecificFiles("**", ".cpp")

	files {"Startup.cpp"}
