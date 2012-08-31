newoption {
	trigger = "platform",
	description = "Target platform for the build"
}

-- This is the platform name used throughout Oak3D premake files
platformName = _OPTIONS["platform"] or "windows32"
print("Building for platform="..platformName)









dofile "src/p4-src.lua"
