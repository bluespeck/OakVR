Solution "Core"

	configuration "linux*"
		buildoptions { "-std=c++11" }
	configuration "linux32"
		buildoptions {"-m32"}
	configuration "linux64"
		buildoptions {"-m64"}

	startproject "OakVR"
	dofile("ResourceManager/p4-ResourceManager.lua")
	dofile("OakVR/p4-OakVR.lua")
