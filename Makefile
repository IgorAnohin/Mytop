all:
	gcc -c *.c
	gcc -o mytop *.o -lncurses
	rm -rf *.o

