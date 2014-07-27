	Project "Text"
		kind "StaticLib"
		language "C++"

		ProjectGlobalConfig()
	
		
		includedirs
		{
			"../../LLAPI",
			"../../Core",
			"../../Core/CoreExternals/FreeType/include",
		}
		
		files { "**.h", "**.cpp" }
		
		links
		{
			"FreeType",
			"ResourceManager",
			"Renderer"
		}
