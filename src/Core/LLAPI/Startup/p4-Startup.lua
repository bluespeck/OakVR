Oak3DProject "Startup"
	kind "StaticLib"
	language "C++"

	includedirs{ ".." }
	
	files {"**.h"}
	Oak3DPlatformSpecificFiles("**_", ".cpp")

	files {"Startup.cpp"}
