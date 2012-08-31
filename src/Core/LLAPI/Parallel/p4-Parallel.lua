project "Parallel"
	kind "StaticLib"
	language "C++"

	files {"**.h", "**_".. platformName ..".cpp", "ThreadFactory.cpp" }
