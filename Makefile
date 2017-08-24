
all:
	$(CC) -std=c99 -g -c *.c
	$(CC) -o mytop *.o -lncurses

clean:
	rm -rf *.o
