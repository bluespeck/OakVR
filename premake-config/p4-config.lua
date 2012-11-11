function ro3dFindSolutionWithProject(projectName)
	for sln in premake.solution.each() do
		prj = premake.solution.findproject(sln, projectName)
		if prj ~= nil then
			return sln
		end
	end

	return nil
end

function ro3dPlatformSpecificFiles(prefix, suffix)
	-- try to get current project
	container = premake.getobject("container")
	if container.platforms == nil then
		-- project doesn't have any specified platforms
		-- try with the solution
		container = container.solution
		if container.platforms == nil then
			return
		end
	end

	for _, plf in ipairs(container.platforms) do
		configuration {plf}
			files { prefix .. plf .. suffix }
	end

end

function ro3dAddBinDirAsLinkDir(prjName)
	prj = premake.getobject("container")
	print("-----"..prj.name)
	for _, cfgname in ipairs(prj.configurations) do
		for _, plfname in ipairs(prj.platforms) do
			configuration { cfgname, plfname }
				libdirs { ro3dRoot .. "/bin/" .. cfgname .. "/" .. plfname }
		end
	end
	configuration {}
end
				
CurrentSln = nil
function ro3dSolution(solutionName)
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
					targetdir (ro3dRoot .. "/bin/" .. cfg .."/".. plf)
			end
		end
		
		configuration {}
		
		location(ro3dRoot .. "/workspace/" .. (_ACTION or "").. "/" .. solutionName)
end

function ro3dProject(projectName)
	project(projectName)
		location(ro3dRoot .. "/workspace/" .. (_ACTION or "") .. "/" .. premake.getobject("solution").name .. "/" .. projectName)
end

