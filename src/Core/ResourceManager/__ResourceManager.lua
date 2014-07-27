	Project "ResourceManager"
		kind "StaticLib"
		language "C++"

		ProjectGlobalConfig()
	
		
		includedirs
		{
			"../../LLAPI",
			"..",
			"../CoreExternals/Png",
			"../CoreExternals/Zlib",
		}
		
		files { "**.h", "**.cpp" }
		
		links
		{
			"Png"
		}
