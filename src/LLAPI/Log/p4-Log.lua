Project "Log"
	kind "StaticLib"
	language "C++"

	includedirs{ ".." }
	
	files {"**.h", "Log.cpp"}
	PlatformSpecificFiles("**_", ".cpp")
