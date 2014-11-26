Project "KeyboardInput"
	kind "StaticLib"
	language "C++"
	ProjectGlobalConfig()
	
	includedirs{ ".", "../.." }
	
	files {"**.h"}
	files {"KeyboardInput.cpp"}
	PlatformSpecificFiles("**_", ".cpp")