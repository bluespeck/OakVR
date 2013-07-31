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
		"ResourceManager",
		"Startup",
		"FileIO",
		"Math",
		"IRenderer",
		"Utils",
		"Input",
	}
	
	configuration {"windows*"}
		links {	"DirectX9Renderer",	"DirectX11Renderer" }
	configuration {"windows* or linux*"}
		links {	"OpenGLRenderer" }
	configuration {}
	
	AddBinDirAsLinkDir(OakVR)
	
