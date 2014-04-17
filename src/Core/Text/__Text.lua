	Project "Text"
		kind "StaticLib"
		language "C++"

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
