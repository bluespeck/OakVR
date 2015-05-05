echo off

if "%1" == "clean" (
	del /S/Q workspace
	del /S/Q bin
)

SET PLF=windows64
SET CFG=debug

echo --------------------------------------------------------------------------
echo --------------------------------------------------------------------------
echo Generating OakVR solution
echo
premake5 vs2015

echo
echo Building OakVR [%PLF%/%CFG%]
echo
premake5 --buildplf=%PLF% --buildcfg=%CFG% build

echo --------------------------------------------------------------------------
echo --------------------------------------------------------------------------
