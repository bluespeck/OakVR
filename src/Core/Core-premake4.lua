	dofile("LLAPI/LLAPI-premake4.lua")

solution "Core"
	configurations { "Debug", "Release" }

	dofile("Math/Math-premake4.lua")
	dofile("Utils/Utils-premake4.lua")
	dofile("ResourceManager/ResourceManager-premake4.lua")
	dofile("Oak3D/Oak3D-premake4.lua")
