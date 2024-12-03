.PHONY: run compile clean

default: run 

compile: shell.o functions.o
	@gcc -o shell shell.o functions.o

shell.o: shell.c functions.h 
	@gcc -c shell.c -Wall

functions.o: functions.c
	@gcc -c functions.c -Wall

run: compile
	@./shell 

clean:
	rm -f *.o shell
