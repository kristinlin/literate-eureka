all: loopy.c
	gcc loopy.c
run: all
	./a.out
