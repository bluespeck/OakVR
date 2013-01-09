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
		location(ro3dRoot .. "/workspace/" .. (_ACTION or "") .. "/" .. premake.getobject("solution").name.. "/" .. "RO3DBuild")
		
		files{ro3dRoot .. "/premake4.lua", "**p4*.lua", ro3dRoot .. "/workspace/" .. (_ACTION or "") .. "/" .. premake.getobject("solution").name.. "/RO3DBuild/buildLog.txt"}
		prebuildcommands {"cd " .. ro3dRoot .. "&& premake4 vs2012 >" .. ro3dRoot .. "/workspace/" .. (_ACTION or "") .. "/" .. premake.getobject("solution").name.. "/RO3DBuild/buildLog.txt"}
		configuration {}