project "Log"
	kind "StaticLib"
	language "C++"

	files {"**.h"}
	Oak3DPlatformSpecificFiles("**_", ".cpp")
