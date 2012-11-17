
	ro3dProject "OpenGLRenderer"
		platforms { "linux32", "linux64", "windows32", "windows64" }
		kind "StaticLib"
		language "C++"
		
		includedirs { "../.." }
		
		files { "**.h", "**.cpp" }
		
		configuration {"linux64"}
			buildoptions {"-fpermissive"}

