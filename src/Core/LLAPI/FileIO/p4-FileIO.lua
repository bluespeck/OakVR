ro3dProject "FileIO"
	kind "StaticLib"
	language "C++"
	
	includedirs
	{
		"..",
	}
	
	files
	{
		"*.h",
	}

	ro3dPlatformSpecificFiles("*_", ".cpp")
