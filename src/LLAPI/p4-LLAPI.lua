Solution "LLAPI"
	configuration "linux*"
		buildoptions { "-std=c++11" }
	configuration "linux32"
		buildoptions {"-m32"}
	configuration "linux64"
		buildoptions {"-m64"}

	dofile("FileIO/p4-FileIO.lua")
	dofile("Input/p4-Input.lua")
	dofile("Math/p4-Math.lua")
	dofile("Renderer/p4-Renderer.lua")
	dofile("Startup/p4-Startup.lua")
	dofile("Log/p4-Log.lua")
	dofile("Utils/p4-Utils.lua")

	configuration {}
