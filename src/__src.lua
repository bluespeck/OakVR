Solution "OAKVR"
	configuration "linux*"
		buildoptions { "-std=c++11" }
	configuration "linux32"
		buildoptions {"-m32"}
	configuration "linux64"
		buildoptions {"-m64"}

dofile("LLAPI/__LLAPI.lua")
dofile("Core/__Core.lua")
-- dofile "Editor"
-- dofile "Leaf3D"


