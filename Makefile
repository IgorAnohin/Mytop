all:
	gcc -g -c *.c
	gcc -o mytop *.o -lncurses -g
	rm -rf *.o

