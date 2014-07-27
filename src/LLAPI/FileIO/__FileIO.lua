Project "FileIO"
	kind "StaticLib"
	language "C++"
	ProjectGlobalConfig()
	
	includedirs
	{
		"..",
	}
	
	files
	{
		"*.h",
		"Path.cpp"
	}

	PlatformSpecificFiles("*_", ".cpp")
