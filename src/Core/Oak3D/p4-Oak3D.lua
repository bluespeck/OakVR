Oak3DProject "Oak3D"
	configuration { "linux*" }
		kind "ConsoleApp"
	configuration { "windows*" }
		kind "WindowedApp"
	configuration {}
	
	language "C++"

	includedirs
	{
		"../LLAPI",
		".."
	}
	
	files { "**.h", "**.cpp" }
	
	
	links
	{
		"Startup",
		"FileIO",
		"Math",
		"IRenderer",
		"Utils"
		
	}
