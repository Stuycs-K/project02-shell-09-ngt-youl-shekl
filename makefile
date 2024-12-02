.PHONY: run compile clean

compile shell: shell.o
	@gcc -o shell shell.o
shell.o: shell.c
	@gcc -c shell.c -Wall
clean:
	rm -f *.o shell
