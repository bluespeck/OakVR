solution "Core"
	configurations { "Debug", "Release" }

	project "Core"
		kind "StaticLib"
		language "C++"
		files { "**.h", "**.cpp" }
