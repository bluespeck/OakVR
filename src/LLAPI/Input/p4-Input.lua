Project "Input"
	kind "StaticLib"
	language "C++"
	
	includedirs{ ".." }
	
	files {"**.h"}
	PlatformSpecificFiles("**_", ".cpp")
