project "Startup"
	kind "StaticLib"
	language "C++"

	files {"**.h", "**_".. platformName ..".cpp", "Startup.cpp"}
