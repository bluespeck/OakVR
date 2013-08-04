Project "OakVR"
	kind "ConsoleApp"
	language "C++"
	

	includedirs
	{
		"../../LLAPI",
		".."
	}
	
	files { "**.h", "**.cpp" }

	configuration {"linux*"}
		excludes {"WindowsRenderWindow.*", "InitWindows.cpp"}	
	configuration {}

	links
	{
		--"ResourceManager",
		"Renderer",
		"Startup",
		"FileIO",
		"Math",
		"Utils",		
		"Time",
		"Log",
		
	}
	
	configuration {"windows*"}
		links {	"DirectX9Renderer",	"DirectX11Renderer" }
	configuration {"linux*"}
		links {	"OpenGLRenderer", "glfw", "GL" }
	configuration {}
	
	AddBinDirAsLinkDir(OakVR)
	
