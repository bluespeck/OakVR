solution("OakVRBuild")
	configurations ("final")
	platforms ("windows32")
	location(oakvrRoot .. "/workspace/" .. (_ACTION or "").. "/" .. "OakVRBuild")
	
	configuration "windows32"
		system "Windows"
		architecture "x32"
	configuration {}
	
	
	project("OakVRBuild")
		kind "StaticLib"
		language "C++"	--from lack of lua

		prjLocation = oakvrRoot .. "/workspace/" .. (_ACTION or "") .. "/" .. premake.api.scope.solution.name.. "/" .. "OakVRBuild"
		location(prjLocation)
		
		logLocation = prjLocation .. "/buildLog.txt"
		files
		{
			oakvrRoot .. "/premake5.lua", 
			oakvrRoot .. "/premake-config/**__*.lua", 
			"**__*.lua", 
			logLocation
		}
		
		postbuildcommands {"cd " .. oakvrRoot .. "&& premake5 vs2012 > " .. logLocation .."&& date /T >>" .. logLocation .." && time /T >> " .. logLocation }
		configuration {}
