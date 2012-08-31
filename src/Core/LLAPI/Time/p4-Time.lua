project "Time"
	kind "StaticLib"
	language "C++"

	files {"**.h", "**_".. platformName ..".cpp"}
