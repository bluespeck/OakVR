solution "LLAPI"
	configurations { "Debug", "Release" }

	dofile("FileSystem/FileSystem-premake4.lua")
	dofile("Input/Input-premake4.lua")
	dofile("Parallel/Parallel-premake4.lua")
	dofile("Time/Time-premake4.lua")
	dofile("Renderer/Renderer-premake4.lua")
	dofile("Startup/Startup-premake4.lua")
