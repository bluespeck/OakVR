solution("RO3DBuild")
	configurations ("final")
	platforms ("windows32")
	location(ro3dRoot .. "/workspace/" .. (_ACTION or "").. "/" .. "RO3DBuild")
	
	configuration "windows32"
		system "Windows"
		architecture "x32"
	configuration {}
	
	
	project("RO3DBuild")
		kind "StaticLib"
		language "C++"	--from lack of lua

		prjLocation = ro3dRoot .. "/workspace/" .. (_ACTION or "") .. "/" .. premake.api.scope.solution.name.. "/" .. "RO3DBuild"
		location(prjLocation)
		
		logLocation = prjLocation .. "/buildLog.txt"
		files
		{
			ro3dRoot .. "/premake4.lua", 
			ro3dRoot .. "/premake-config/**p4*.lua", 
			"**p4*.lua", 
			logLocation
		}
		
		postbuildcommands {"cd " .. ro3dRoot .. "&& premake4 vs2012 > " .. logLocation .."&& date /T >>" .. logLocation .." && time /T >> " .. logLocation }
		configuration {}
