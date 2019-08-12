Workspace "OakMeshConverter"
	configuration "linux*"
		buildoptions { "-std=c++17" }
	configuration "linux32"
		buildoptions {"-m32"}
	configuration "linux64"
		buildoptions {"-m64"}
			
	Project "OakVRMeshConverter"
		kind "ConsoleApp"
		language "C++"
		ProjectGlobalConfig()
	
		
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