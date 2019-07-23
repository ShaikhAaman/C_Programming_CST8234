CC = gcc
CC_FLAGS =  -g -std=c99 -pedantic -W -Wall -D_POSIX_SOURCE -Wno-unused-parameter
FILES = main.c child.c parent.c
OUT_EXE = ass2 

build: $(FILES)
	   $(CC) $(CC_FLAGS) -o $(OUT_EXE) $(FILES)

clean: rm -f *.o core *.exe *~

rebuild: clean build
