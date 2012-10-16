project "Startup"
	kind "StaticLib"
	language "C++"

	files {"**.h"}
	Oak3DPlatformSpecificFiles("**_", ".cpp")

	files {"Startup.cpp"}
