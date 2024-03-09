main.o: main.c
	cc -std=c2x -c main.c
build: main.o
	cc -std=c2x -L. -ltree-sitter -ltree-sitter-scala -o main main.o
