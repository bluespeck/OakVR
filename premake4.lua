--newoption {
--	trigger = "platform",
--	description = "Target platform for the build"
--}

function newplatform(plf)
    local name = plf.name
    local description = plf.description
 
    -- Register new platform
    premake.platforms[name] = {
        cfgsuffix = "_"..name,
        iscrosscompiler = true
    }
 
	-- Allow use of new platform in --platfroms
    table.insert(premake.option.list["platform"].allowed, { name, description })
    table.insert(premake.fields.platforms.allowed, name)
 
    -- Add compiler support
    -- gcc
    premake.gcc.platforms[name] = plf.gcc
    --other compilers (?)
end
 
function newgcctoolchain(toolchain)
    newplatform {
        name = toolchain.name,
        description = toolchain.description,
        gcc = {
            cc = toolchain.prefix .. "gcc",
            cxx = toolchain.prefix .. "g++",
            ar = toolchain.prefix .. "ar",
			as = toolchain.prefix .. "as",
			ld = toolchain.prefix .. "ld",
            cppflags = "-MMD " .. toolchain.cppflags
        }
    }
end

-- The folder in which this file resides should be the top Oak3D folder
Oak3DRoot = os.getcwd()

-- This is the platform name used throughout Oak3D premake files
platformName = _OPTIONS["platform"] or "windows32"

print("----------------------------------------")
print("--")
print("-- Current platform: " .. platformName)
print("--")
print("----------------------------------------")

dofile "premake-config/p4-config.lua"
dofile "src/p4-src.lua"
