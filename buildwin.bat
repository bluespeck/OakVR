if "%1" == "clean" (
	del /S/Q workspace
	del /S/Q bin
)

premake5 vs2013
premake5 --buildplf=windows64 --buildcfg=debug build
