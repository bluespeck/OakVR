Oak3DProject "FileIO"
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

	Oak3DPlatformSpecificFiles("*_", ".cpp")
