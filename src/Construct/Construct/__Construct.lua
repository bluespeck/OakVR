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
	
	configuration {"windows64"}
		links { "opengl32" }
		buildoptions {"/std:c++latest"}