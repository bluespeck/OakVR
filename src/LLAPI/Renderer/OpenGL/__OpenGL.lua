
	Project "OpenGLRenderer"
		platforms { "linux32", "linux64", "windows32", "windows64" }
		kind "StaticLib"
		language "C++"
		ProjectGlobalConfig()
	
		includedirs { "../.." }
		
		files { "*.h", "*.cpp" }
		
		links { "Profiler" }
		
		defines { "_CRT_SECURE_NO_WARNINGS" }
		
		ExcludePlatformSpecificFiles("*_", ".cpp")
		PlatformSpecificFiles("*_", ".cpp")
		
		configuration {"linux*"}
			defines { "GL_GLEXT_PROTOTYPES" }
			buildoptions {"-fpermissive"}
			links { "opengl", "glfw", "GLEW", "GL", "Math" }
			
		configuration { "windows*" }
			-- glfw
			includedirs { "GLFW/include" }
			
			defines { "_GLFW_WIN32", "_GLFW_USE_OPENGL", "_GLFW_WGL" }
			files {
				"GLFW/src/clipboard.c",				
				"GLFW/src/context.c",
				"GLFW/src/gamma.c",
				"GLFW/src/init.c",
				"GLFW/src/input.c",
				"GLFW/src/joystick.c",
                "GLFW/src/monitor.c",
				"GLFW/src/time.c",
				"GLFW/src/wgl_context.c",
				"GLFW/src/window.c",
				"GLFW/src/win32*.c",
			}
			
			-- glew
			includedirs { "GLEW/include" }
			defines { "GLEW_STATIC" }
			files { "GLEW/src/*.c" }
			
			-- opengl
			defines { "GL_GLEXT_PROTOTYPES" }
		configuration {}
		

