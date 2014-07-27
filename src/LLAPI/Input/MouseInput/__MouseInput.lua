Project "MouseInput"
	kind "StaticLib"
	language "C++"
	ProjectGlobalConfig()
	
	includedirs{ ".", "../.." }
	
	files {"**.h"}
	PlatformSpecificFiles("**_", ".cpp")
