-- Oak3D supported platforms
supportedPlatforms = {
	"windows32",
	"windows64",
	"linux32",
	"linux64"
}

for _, v in ipairs(supportedPlatforms) do
	dofile("p4-config-" .. v .. ".lua")
end

