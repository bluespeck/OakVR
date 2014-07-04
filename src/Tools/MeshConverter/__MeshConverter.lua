Solution "OakMeshConverter"
	configuration "linux*"
		buildoptions { "-std=c++11" }
	configuration "linux32"
		buildoptions {"-m32"}
	configuration "linux64"
		buildoptions {"-m64"}
			
	Project "OakVRMeshConverter"
		kind "ConsoleApp"
		language "C++"
		
		files { "**.h", "**.cpp" }

		includedirs 
		{
			"../../LLAPI",
			"../../Core/CoreExternals",
		}
		
		links
		{
			"TinyXML2"
		}