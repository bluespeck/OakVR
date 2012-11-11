function Oak3DFindSolutionWithProject(projectName)
	for sln in premake.solution.each() do
		prj = premake.solution.findproject(sln, projectName)
		if prj ~= nil then
			return sln
		end
	end

	return nil
end

function Oak3DPlatformSpecificFiles(prefix, suffix)
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
				
CurrentSln = nil
function Oak3DSolution(solutionName)
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
					targetdir (Oak3DRoot .. "/bin/" .. cfg .."/".. plf)
			end
		end
		
		configuration {}
		
		location(Oak3DRoot .. "/workspace/" .. (_ACTION or "").. "/" .. solutionName)
end

function Oak3DProject(projectName)
	project(projectName)
		location(Oak3DRoot .. "/workspace/" .. (_ACTION or "") .. "/" .. premake.getobject("solution").name .. "/" .. projectName)
end

