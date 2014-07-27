Project "KeyboardInput"
	kind "StaticLib"
	language "C++"
	ProjectGlobalConfig()
	
	includedirs{ ".", "../.." }
	
	files {"**.h"}
	PlatformSpecificFiles("**_", ".cpp")