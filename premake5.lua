-- The folder in which this file resides should be the top Oak3D folder
oakvrRoot = os.getcwd()

dofile "premake-config/p4-config.lua"

if _ACTION == "build" then
	Build((_OPTIONS["buildplf"] or "linux64"), (_OPTIONS["buildcfg"] or "fastdebug"))
else
	dofile "src/p4-meta.lua"
	dofile "src/p4-src.lua"
end


