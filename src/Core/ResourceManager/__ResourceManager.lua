	Project "ResourceManager"
		kind "StaticLib"
		language "C++"

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
