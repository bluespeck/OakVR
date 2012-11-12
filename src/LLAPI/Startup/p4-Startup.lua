ro3dProject "Startup"
	kind "StaticLib"
	language "C++"

	includedirs{ ".." }
	
	files {"*.h"}
	ro3dPlatformSpecificFiles("**_", ".cpp")

	files {"Startup.cpp"}
