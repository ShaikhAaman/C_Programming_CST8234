CC = gcc
CC_FLAGS = -ansi -g -pedantic -Wall -W -std=c89 -Wno-unused-parameter

FILES = assignment1.c 
OUT_EXE = assignment1

build: $(FILES)
	$(CC) $(CC_FLAGS) -o $(OUT_EXE) $(FILES) 

clean:
	rm -f *.o core *.exe *~ *.out *.stackdump

rebuild: clean build
