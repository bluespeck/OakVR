solution "LLAPI"
	configurations { "Debug", "Release" }
	--platforms {"native", "windows32", "windows64", "linux32", "linux64"}
	location(Oak3DRoot .. "/workspace/" .. _ACTION .. "/LLAPI")
	--todo Temporary; please remove
	configuration "linux*"
		buildoptions {"-std=c++0x"}
	configuration {}
	
	dofile("FileIO/p4-FileIO.lua")
	dofile("Input/p4-Input.lua")
	dofile("Parallel/p4-Parallel.lua")
	dofile("Time/p4-Time.lua")
	dofile("Renderer/p4-Renderer.lua")
	dofile("Startup/p4-Startup.lua")
	dofile("Log/p4-Log.lua")
