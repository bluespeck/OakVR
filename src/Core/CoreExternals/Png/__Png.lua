Project "Png"
	kind "StaticLib"
	language "C++"
	
	ProjectGlobalConfig()

	-- Png version 1.6.10 (06.Mar.2014)
	includedirs
	{
		".",
		"../Zlib",
	}
	
	files
	{
		"png.h",
		"pngconf.h",
		"pnglibconf.h",
		"pngdebug.h",
		"pnginfo.h",
		"pngpriv.h",
		"pngstruct.h",
		"png.c",
		"pngerror.c",
		"pngget.c",
		"pngmem.c",
		"pngpread.c",
		"pngread.c",
		"pngrio.c",
		"pngrtran.c",
		"pngrutil.c",
		"pngset.c",
		"pngtrans.c",
		"pngwio.c",
		"pngwrite.c",
		"pngwtran.c",
		"pngwutil.c",
	}
	
	defines { "_CRT_SECURE_NO_WARNINGS" }
	
	links { "Zlib" }
