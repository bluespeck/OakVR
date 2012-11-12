ro3dProject "ro3d"
	kind "ConsoleApp"
	
	language "C++"

	includedirs
	{
		"../../LLAPI",
		".."
	}
	
	files { "**.h", "**.cpp" }
	
	links
	{
		"ResourceManager",
		"Startup",
		"FileIO",
		"Math",
		"IRenderer",
		"Utils",
		"Input",
		"Time",
		"Parallel",
		"DirectX9Renderer",
		"DirectX11Renderer"
	
		
	}
	
	ro3dAddBinDirAsLinkDir(ro3d)
	