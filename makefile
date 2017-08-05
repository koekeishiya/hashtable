all:
	rm -rf ./bin
	mkdir -p ./bin
	clang ./src/main.c -o ./bin/main
