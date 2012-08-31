project "FileSystem"
	kind "StaticLib"
	language "C++"

	files {"**.h", "**_".. platformName ..".cpp"}
