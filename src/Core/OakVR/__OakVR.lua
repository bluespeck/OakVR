Project "OakVR"
	kind "StaticLib"
	language "C++"
	
	ProjectGlobalConfig()
	
	includedirs
	{
		"../../LLAPI",
		"../../Core"
	}
	
	files { "**.h", "**.cpp" }

	configuration {}

	links
	{
		"Text",
		"MouseInput",
		"KeyboardInput",
		"Renderer",
		"ResourceManager",
		"Startup",
		"FileIO",
		"Math",
		"Time",
		"Log",
		"Profiler",
	}
	
	configuration {"windows*"}
		--links {	"DirectX11Renderer" }
		links {	"OpenGLRenderer" }
		--linkoptions { "OpenGL32.lib" }
	configuration {"linux*"}
		links {	"OpenGLRenderer", "glfw", "GLEW", "GL" }
		
	configuration {"windows32"}
		libdirs { (os.getenv("GLEW_PATH") or "") .. "/lib/Release/Win32" }
		links { "glew32s", "opengl32" }
	configuration {"windows64"}
		libdirs { (os.getenv("GLEW_PATH") or "") .. "/lib/Release/x64" }
		links { "glew32s", "opengl32" }
	configuration {}
	
	AddBinDirAsLinkDir(OakVR)
	
