Project "DeferredRenderer"
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
		"Renderer",
		"ResourceManager",
		"Math",
		"Time",
		"Log",
		"Profiler",
		"Utils"
	}
	
	configuration {"windows*"}
		--links {	"DirectX11Renderer" }
		links {	"OpenGLRenderer" }
		--linkoptions { "OpenGL32.lib" }
	configuration {"linux*"}
		links {	"OpenGLRenderer"}
	configuration {}
	
	AddBinDirAsLinkDir(OakVR)
	
