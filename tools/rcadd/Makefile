override BIN=rcadd
override INCPATH=-I../../
override LIBPATH=-L../../bin
override OBJS=$(shell ls *.c | sed -e "s/\.c/.o/g")
override FLAGS+=-lreclass

# These will be used when the Makefile is called directly
CC=gcc
FLAGS=-Wall -fPIC -ggdb

all: $(OBJS)
	$(CC) $(INCPATH) $(LIBPATH) $(OBJS) $(FLAGS) -o $(BIN)

%.o: %.c
	$(CC) $(INCPATH) $(LIBPATH) $(FLAGS) -c $<

clean:
	-rm $(OBJS)
	-rm $(BIN)


install:
	cp $(BIN) $(INSTALL_BIN_DIR)
