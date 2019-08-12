allowedPlatforms = { "windows64", "linux64", }
allowedConfigs = { "debug", "fastdebug", "profile", "final"}

function GetTableWithDescriptions(_table)
	local tbl = {}
	for _, value in pairs(_table) do
		table.insert(tbl, {value, ""})
	end
	
	return tbl
end

newoption {
	trigger = "buildplf",
	value   = "VALUE",
	description = "Set the platform for which the build is done",
	allowed = GetTableWithDescriptions(allowedPlatforms)
}

newoption {
	trigger = "buildcfg",
	value   = "VALUE",
	description = "Set the configuration for which the build is done",
	allowed = GetTableWithDescriptions(allowedConfigs)
}

newaction {
		trigger         = "build",
		shortname       = "Build",
		description     = "Builds the solution for given buildplatform and buildconfig",

		-- temporary, until I can phase out the legacy implementations
		isnextgen = true,

		valid_kinds     = { },

		valid_languages = { "C", "C++", "C#" },

		valid_tools     = {
			cc     = { },
			dotnet = { }
		},

		onsolution = function(sln)

		end,

		onproject = function(prj)
			
		end,

		oncleansolution = function(sln)

		end,

		oncleanproject = function(prj)

		end
	}

function FindSolutionWithProject(projectName)
	for sln in premake.solution.each() do
		prj = premake.solution.findproject(sln, projectName)
		if prj ~= nil then
			return sln
		end
	end

	return nil
end

function PlatformSpecificFiles(prefix, suffix)
	-- try to get current project
	local container = premake.api.scope.project
	if container.platforms == nil then
		-- project does not have any specified platforms
		-- try with the solution
		container = premake.api.scope.project.solution
		if container.platforms == nil then
			return
		end
	end

	for _, plf in ipairs(container.platforms) do
		configuration {plf}
			files { prefix .. plf .. suffix }
	end

	configuration {}
end

function ExcludePlatformSpecificFiles(prefix, suffix)
	-- try to get current project
	local container = premake.api.scope.project
	if container.platforms == nil then
		-- project does not have any specified platforms
		-- try with the solution
		container = premake.api.scope.project.solution
		if container.platforms == nil then
			return
		end
	end
	configuration {}	
	for _, plf in ipairs(container.platforms) do
		removefiles( prefix .. plf .. suffix) 
	end

	configuration {}
end

function AddBinDirAsLinkDir(prjName)
	prj = premake.api.scope.project
	for _, cfgname in ipairs(prj.configurations) do
		for _, plfname in ipairs(prj.platforms) do
			configuration { cfgname, plfname }
				libdirs { oakvrRoot .. "/bin/" .. cfgname .. "/" .. plfname }
		end
	end
	configuration {}
end
				
CurrentSln = nil
function Workspace(workspaceName)
	print("### Configuring workspace(" .. workspaceName .. ") ###")

	CurrentSln = workspace (workspaceName)
		plfs = allowedPlatforms
		cfgs = allowedConfigs

		platforms (plfs)		
		configurations (cfgs)
		
	
		configuration "debug"
			symbols "On"
			defines		{ "OAKVR_DEBUG" }

		configuration "fastdebug"
			symbols "On"
			optimize "Speed"
			defines		{ "OAKVR_FASTDEBUG" }

		configuration "profile"
			optimize "Speed"	
			defines		{ "OAKVR_PROFILE" }

		configuration "final"
			optimize "Speed"
			defines		{ "OAKVR_FINAL" }

		configuration "linux64"
			system "Linux"
			architecture "x64"
			toolset "clang"
			defines		{ "OAKVR_LINUX64" }

		configuration "windows64"
			system "Windows"
			architecture "x64"
			staticruntime "On"
			--toolset "msc"	
			defines		{ "OAKVR_WINDOWS64" }
			buildoptions { "/std:c++latest" }
		
		for _, cfg in ipairs(cfgs) do
			for _, plf in ipairs(plfs) do
				configuration { cfg, plf }
					targetdir (oakvrRoot .. "/bin/" .. cfg .."/".. plf)
			end
		end
		
		configuration {}
		
		location(oakvrRoot .. "/workspace/" .. (_ACTION or "").. "/" .. workspaceName)
end

function Project(projectName)
	project(projectName)
		location(oakvrRoot .. "/workspace/" .. (_ACTION or "") .. "/" .. premake.api.scope.workspace.name .. "/" .. projectName)
		systemversion ("10.0.15063.0")
end

function ProjectGlobalConfig()
end

function Build(plf, cfg)
	local wsFolder = "workspace"
	if plf == "linux64" or plf == "linux32" then
		os.execute("cd " .. wsFolder .. "/gmake/OAKVR && make config=".. cfg .. "_"..plf)
	elseif plf == "windows64" or plf == "windows32" then
		print("Build action not implemented for this platform!\n")
	end
end


