Project "Zlib"
	kind "StaticLib"
	language "C++"

	-- current version 1.2.8 (28 Apr 2013)
	includedirs
	{
		".",
	}
	
	files
	{
		"zconf.h",
		"zlib.h",
		"crc32.h",
		"deflate.h",
		"gzguts.h",
		"inffast.h",
		"inffixed.h",
		"inflate.h",
		"inftrees.h",
		"trees.h",
		"zutil.h",
		"adler32.c",
		"compress.c",
		"crc32.c",
		"deflate.c",
		"gzclose.c",
		"gzlib.c",
		"gzread.c",
		"gzwrite.c",
		"inflate.c",
		"infback.c",
		"inftrees.c",
		"inffast.c",
		"trees.c",
		"uncompr.c",
		"zutil.c",
	}
	