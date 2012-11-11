Oak3DSolution "LLAPI"
	configuration "linux*"
		buildoptions { "-std=c++0x" }

	dofile("FileIO/p4-FileIO.lua")
	dofile("Input/p4-Input.lua")
	dofile("Parallel/p4-Parallel.lua")
	dofile("Time/p4-Time.lua")
	dofile("Math/p4-Math.lua")
	dofile("Renderer/p4-Renderer.lua")
	dofile("Startup/p4-Startup.lua")
	dofile("Log/p4-Log.lua")
	dofile("Utils/p4-Utils.lua")

	configuration {}