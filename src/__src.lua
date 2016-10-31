Solution "OAKVR"
	startproject "Oakraft"
	configuration "linux*"
		buildoptions { "-std=c++11" }
	configuration "linux32"
		buildoptions {"-m32"}
	configuration "linux64"
		buildoptions {"-m64"}
	configuration "windows"
		buildoptions {"/std:c++latest"}

dofile("LLAPI/__LLAPI.lua")
dofile("Core/__Core.lua")
dofile("Construct/__Construct.lua")
dofile("Oakraft/__Oakraft.lua")


dofile("Tools/__Tools.lua")
-- dofile "Editor"
-- dofile "Leaf3D"


