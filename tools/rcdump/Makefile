CC=gcc
FLAGS=-Wall -L../bin -I../ -lreclass -ggdb

all:
	$(CC) helper.c -c $(FLAGS)
	$(CC) reclass_dump.c helper.o -o rcdump $(FLAGS)

clean:
	rm helper.o
	rm rcdump
