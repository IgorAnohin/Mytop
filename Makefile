all:
	gcc -g -c *.c
	gcc -o mytop *.o -lncurses

clean:
	rm -rf *.o
