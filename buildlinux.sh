if [ "$1" == "clean" ]; then
	rm -r ./workspace
	rm -r ./bin
fi

./premake4 gmake
./premake4 --buildplf=linux64 --buildcfg=debug build
