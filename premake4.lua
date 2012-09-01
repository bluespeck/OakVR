newoption {
	trigger = "platform",
	description = "Target platform for the build"
}

-- This is the platform name used throughout Oak3D premake files
platformName = _OPTIONS["platform"] or "windows32"

-- The folder in which this file resides should be the top Oak3D folder
Oak3DRoot = os.getcwd()

print("----------------------------------------")
print("--")
print("-- Current platform: " .. platformName)
print("--")
print("----------------------------------------")



dofile "src/p4-src.lua"
