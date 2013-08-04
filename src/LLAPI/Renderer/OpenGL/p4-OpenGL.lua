
	Project "OpenGLRenderer"
		platforms { "linux32", "linux64", "windows32", "windows64" }
		kind "StaticLib"
		language "C++"
		
		includedirs { "../.." }
		
		files { "**.h", "**.cpp" }
		
		ExcludePlatformSpecificFiles("*_", ".cpp")
		PlatformSpecificFiles("*_", ".cpp")
		
		configuration {"linux64"}
			buildoptions {"-fpermissive"}
			links { "opengl", "glfw", "GL" }

