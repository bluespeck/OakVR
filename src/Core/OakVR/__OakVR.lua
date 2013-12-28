Project "OakVR"
	kind "ConsoleApp"
	language "C++"
	

	includedirs
	{
		"../../LLAPI",
		".."
	}
	
	files { "**.h", "**.cpp" }

	configuration {}

	links
	{
		--"ResourceManager",
		"Renderer",
		"Startup",
		"FileIO",
		"Math",
		"Time",
		"Log",
		
	}
	
	configuration {"windows*"}
		--links {	"DirectX11Renderer" }
		links {	"OpenGLRenderer" }
	configuration {"linux*"}
		links {	"OpenGLRenderer", "glfw", "GLEW", "GL" }
	configuration {}
	
	AddBinDirAsLinkDir(OakVR)
	
