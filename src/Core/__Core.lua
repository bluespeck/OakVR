--[[Solution "Core"

	configuration "linux*"
		buildoptions { "-std=c++11" }
	configuration "linux32"
		buildoptions {"-m32"}
	configuration "linux64"
		buildoptions {"-m64"}
	configuration {}
]]
	startproject "OakVR"

	dofile("ResourceManager/__ResourceManager.lua")
	dofile("OakVR/__OakVR.lua")
