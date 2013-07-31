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
function Solution(solutionName)
	print("### Configuring solution(" .. solutionName .. ") ###")

	CurrentSln = solution (solutionName)
		cfgs = { "debug", "fastdebug", "profile", "final"}
		configurations (cfgs)
		plfs = { "linux32", "linux64", "windows32", "windows64" }
		platforms (plfs)
	
		configuration "debug"
			flags       { "Symbols" }

		configuration "fastdebug"
			flags       { "OptimizeSpeed", "Symbols" }

		configuration "profile"
			flags       { "OptimizeSpeed" }	

		configuration "final"
			flags		{ "OptimizeSpeed" }

		configuration "linux32"
			system "Linux"
			architecture "x32"
			toolset "gcc"
		
		configuration "linux64"
			system "Linux"
			architecture "x64"
			toolset "gcc"

		configuration "windows32"
			system "Windows"
			architecture "x32"
			--toolset "msc"

		configuration "windows64"
			system "Windows"
			architecture "x64"
			--toolset "msc"	
		
		for _, cfg in ipairs(cfgs) do
			for _, plf in ipairs(plfs) do
				configuration { cfg, plf }
					targetdir (oakvrRoot .. "/bin/" .. cfg .."/".. plf)
			end
		end
		
		configuration {}
		
		location(oakvrRoot .. "/workspace/" .. (_ACTION or "").. "/" .. solutionName)
end

function Project(projectName)
	project(projectName)
		location(oakvrRoot .. "/workspace/" .. (_ACTION or "") .. "/" .. premake.api.scope.solution.name .. "/" .. projectName)
end

