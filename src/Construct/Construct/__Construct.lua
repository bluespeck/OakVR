Project "Construct"
	kind "ConsoleApp"
	language "C++"
	
	includedirs
	{
		"../../LLAPI",
		"../../Core"
	}
	
	files { "**.h", "**.cpp" }
	
	links {"OakVR"}
	
	configuration {"windows32"}
		libdirs { (os.getenv("GLEW_PATH") or "") .. "/lib/Release/Win32" }
		links { "glew32s", "opengl32" }
	configuration {"windows64"}
		libdirs { (os.getenv("GLEW_PATH") or "") .. "/lib/Release/x64" }
		links { "glew32s", "opengl32" }