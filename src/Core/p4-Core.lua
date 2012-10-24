	dofile("LLAPI/p4-LLAPI.lua")

Oak3DSolution "Core"
	location(Oak3DRoot .."/workspace/" .. (_ACTION or "") .. "/Core")

	dofile("Utils/p4-Utils.lua")
	dofile("ResourceManager/p4-ResourceManager.lua")
	dofile("Oak3D/p4-Oak3D.lua")
