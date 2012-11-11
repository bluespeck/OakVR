ro3dProject "Input"
	kind "StaticLib"
	language "C++"
	
	includedirs{ ".." }
	
	files {"**.h"}
	ro3dPlatformSpecificFiles("**_", ".cpp")
