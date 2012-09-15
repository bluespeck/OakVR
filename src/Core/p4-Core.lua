	dofile("LLAPI/p4-LLAPI.lua")

solution "Core"
	configurations { "Debug", "Release" }
	--platforms {"native", "windows32", "windows64", "linux32", "linux64"}
	location(Oak3DRoot .."/workspace/" .. _ACTION .. "/Core")

	dofile("Math/p4-Math.lua")
	dofile("Utils/p4-Utils.lua")
	dofile("ResourceManager/p4-ResourceManager.lua")
	dofile("Oak3D/p4-Oak3D.lua")
