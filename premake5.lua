-- The folder in which this file resides should be the top Oak3D folder
oakvrRoot = os.getcwd()

dofile "premake-config/__config.lua"

if _ACTION == "build" then
	Build((_OPTIONS["buildplf"] or "windows64"), (_OPTIONS["buildcfg"] or "fastdebug"))
else
	dofile "src/__meta.lua"
	dofile "src/__src.lua"
end


