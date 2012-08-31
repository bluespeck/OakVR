solution "LLAPI"
	configurations { "Debug", "Release" }
	--platforms {"windows32", "windows64", "linux32", "linux64"}
	location("_build/" .. _ACTION)

	dofile("FileSystem/p4-FileSystem.lua")
	dofile("Input/p4-Input.lua")
	dofile("Parallel/p4-Parallel.lua")
	dofile("Time/p4-Time.lua")
	dofile("Renderer/p4-Renderer.lua")
	dofile("Startup/p4-Startup.lua")
