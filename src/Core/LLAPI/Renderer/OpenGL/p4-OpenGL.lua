
	project "OpenGL"
		platforms { "linux32", "linux64", "windows32", "windows64" }
		kind "StaticLib"
		language "C++"
		
		files { "**.h", "**.cpp" }

