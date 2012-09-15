project "Log"
	kind "StaticLib"
	language "C++"

	files {"**.h", "**_".. platformName ..".cpp"}
