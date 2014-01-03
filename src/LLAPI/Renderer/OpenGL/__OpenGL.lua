
	Project "OpenGLRenderer"
		platforms { "linux32", "linux64", "windows32", "windows64" }
		kind "StaticLib"
		language "C++"
		
		includedirs { "../.." }
		
		files { "*.h", "*.cpp" }
		
		ExcludePlatformSpecificFiles("*_", ".cpp")
		PlatformSpecificFiles("*_", ".cpp")
		
		configuration {"linux*"}
			defines { "GL_GLEXT_PROTOTYPES" }
			buildoptions {"-fpermissive"}
			links { "opengl", "glfw", "GLEW", "GL" }
			
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
			-- opengl
	-- make sure you add GLEW_PATH to the Windows environment variables
			includedirs { (os.getenv("GLEW_PATH") or "") .."/include" }
			defines { "GLEW_STATIC", "GL_GLEXT_PROTOTYPES" }
		configuration {}
		

