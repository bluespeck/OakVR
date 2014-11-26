	Project "Console"
		kind "StaticLib"
		language "C++"

		ProjectGlobalConfig()
	
		
		includedirs
		{
			"../../LLAPI",
			"../../Core",
		}
		
		files { "**.h", "**.cpp" }
		
		links
		{
			"ResourceManager",
			"Renderer"
		}
