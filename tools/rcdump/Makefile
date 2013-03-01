override BIN=rcdump
override INCPATH=-I../../
override LIBPATH=-L../../bin
override OBJS=$(shell ls *.c | sed -e "s/\.c/.o/g")
override FLAGS+=-lreclass

all: $(OBJS)
	$(CC) $(INCPATH) $(LIBPATH) $(OBJS) $(FLAGS) -o $(BIN)

%.o: %.c
	$(CC) $(INCPATH) $(LIBPATH) $(FLAGS) -c $<

clean:
	-rm $(OBJS)
	-rm $(BIN)


install:
	cp $(BIN) $(INSTALL_BIN_DIR)
