	ro3dProject "ResourceManager"
		kind "StaticLib"
		language "C++"

		includedirs
		{
			"../LLAPI",
			".."
		}
		
		files { "**.h", "**.cpp" }
