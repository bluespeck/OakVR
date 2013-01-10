ro3dSolution "Core"

	configuration "linux*"
		buildoptions { "-std=c++11" }
	configuration "linux32"
		buildoptions {"-m32"}
	configuration "linux64"
		buildoptions {"-m64"}

	startproject "ro3d"
	dofile("ResourceManager/p4-ResourceManager.lua")
	dofile("ro3d/p4-ro3d.lua")
