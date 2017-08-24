
EXE = mytop

all:
	$(CC) -std=c99 -g -c *.c
	$(CC) -o $(EXE) *.o -lncurses

clean:
	rm -rf *.o
	rm -f $(EXE)
