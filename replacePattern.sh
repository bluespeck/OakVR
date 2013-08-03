echo "Are you sure you want to replace <<<$1>>> with <<<$2>>> in all source files? (yes to confirm)"
read answer

if [ "$answer" == "yes" ]; then
	for line in $(find src -name "*.cpp" -o -name "*.h" -o -name "*.inc"); do
		sed -e s/"$1"/"$2"/g "$line" > "$line".tmp && mv "$line".tmp "$line"
	done
else
	echo "Operation cancelled!"
fi
