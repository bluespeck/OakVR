	Project "ResourceManager"
		kind "StaticLib"
		language "C++"

		includedirs
		{
			"../../LLAPI",
			".."
		}
		
		files { "**.h", "**.cpp" }
