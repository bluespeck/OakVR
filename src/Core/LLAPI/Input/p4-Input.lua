Oak3DProject "Input"
	kind "StaticLib"
	language "C++"
	
	includedirs{ ".." }
	
	files {"**.h"}
	Oak3DPlatformSpecificFiles("**_", ".cpp")
