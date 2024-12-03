.PHONY: run compile clean

default: run 

compile: shell.o functions.o
	@gcc -o shell shell.o functions.o

shell.o: shell.c
	@gcc -c shell.c -Wall

functions.o: funcitons.c
	@gcc -c funcitons.c -Wall

run: compile
	@./shell 

clean:
	rm -f *.o shell
