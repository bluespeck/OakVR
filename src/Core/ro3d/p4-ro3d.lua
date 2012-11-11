ro3dProject "ro3d"
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
