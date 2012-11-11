Oak3DProject "Log"
	kind "StaticLib"
	language "C++"

	includedirs{ ".." }
	
	files {"**.h"}
	Oak3DPlatformSpecificFiles("**_", ".cpp")
