--[[Workspace "LLAPI"
	configuration "linux*"
		buildoptions { "-std=c++17" }
	configuration "linux32"
		buildoptions {"-m32"}
	configuration "linux64"
		buildoptions {"-m64"}
]]
	dofile("FileIO/__FileIO.lua")
	dofile("Input/__Input.lua")
	dofile("Log/__Log.lua")
	dofile("Math/__Math.lua")
	dofile("Renderer/__Renderer.lua")
	dofile("Startup/__Startup.lua")
	dofile("Time/__Time.lua")
	dofile("Utils/__Utils.lua")
	dofile("Profiler/__Profiler.lua")

	configuration {}
