ro3dProject "ro3d"
	kind "ConsoleApp"
	language "C++"

	includedirs
	{
		"../../LLAPI",
		".."
	}
	
	files { "**.h", "**.cpp" }

	configuration {"linux*"}
		excludes {"WindowsRenderWindow.*", "ro3dInitWindows.cpp"}	
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
	
	ro3dAddBinDirAsLinkDir(ro3d)
	
