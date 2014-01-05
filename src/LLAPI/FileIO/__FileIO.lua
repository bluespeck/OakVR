Project "FileIO"
	kind "StaticLib"
	language "C++"
	
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
