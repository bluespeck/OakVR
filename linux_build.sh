if [ "$1" == "clean" ]; then
	rm -r ./workspace
	rm -r ./bin
fi

./premake5 gmake
./premake5 --buildplf=linux64 --buildcfg=debug build

