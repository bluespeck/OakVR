Oak3DProject "Time"
	kind "StaticLib"
	language "C++"

	includedirs{ ".." }
	
	files {"**.h"}
	Oak3DPlatformSpecificFiles("**_", ".cpp")
