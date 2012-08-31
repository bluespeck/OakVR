	dofile("LLAPI/p4-LLAPI.lua")

solution "Core"
	configurations { "Debug", "Release" }

	dofile("Math/p4-Math.lua")
	dofile("Utils/p4-Utils.lua")
	dofile("ResourceManager/p4-ResourceManager.lua")
	dofile("Oak3D/p4-Oak3D.lua")
