./premake4 gmake
# triggering a relink
rm ./workspace/gmake/Core/OakVR/obj/linux64/fastdebug/oakvr.o
./premake4 --buildplf=linux64 --buildcfg=fastdebug build
