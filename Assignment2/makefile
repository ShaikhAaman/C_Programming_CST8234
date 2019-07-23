CC = gcc
CC_FLAGS = -g -std=c99 -pedantic -W -Wall
FILES = main.c rental.c node.c sort.c
OUT_EXE = ass1

build: $(FILES)
	$(CC) $(CC_FLAGS) -o $(OUT_EXE) $(FILES)

clean:
	rm -f *.o core *.exe *~

rebuild: clean build
