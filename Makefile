BIN=libreclass
CC=gcc
FLAGS=-Wall -fPIC -ggdb
FLAGS+= -DDEBUG


OBJS=$(shell ls *.c | sed -e "s/\.c/.o/g")
HEADERS=$(shell ls *.h)
YACC=bison

PREFIX=/usr/local
INSTALL_INCLUDE_DIR=/usr/include/reclass
INSTALL_LIBS_DIR=$(PREFIX)/lib
INSTALL_BIN_DIR=$(PREFIX)/bin


export

all: shared static tools
	@#$(MAKE) -C tools/rcadd/
	$(MAKE) -C tools/rcdump/
	@#$(MAKE) -C tools/rcmerge/

parser:
	bison -d parser.y
	flex parser.l
	$(CC) $(FLAGS) parser.tab.c parser.tab.h -c
	$(CC) $(FLAGS) lex.yy.c -c
	
	$(eval $OBJS+=parser.tab.o lex.yy.o)
	
shared: parser $(OBJS)
	$(CC) $(FLAGS) $(OBJS) -lfl -shared -o bin/$(BIN).so

static: parser $(OBJS)
	ar rcs bin/$(BIN).a $(OBJS)

%.o: %.c
	$(CC) $(FLAGS) -c $<

clean:
	-rm -f *.o
	-rm -f *.so
	-rm -f *.a
	-rm -f *.gch
	-rm -f parser.tab.c parser.tab.h lex.yy.c
	-rm -rf bin/*.so
	-rm -rf bin/*.a

	@#-$(MAKE) -C tools/rcadd/ clean
	-$(MAKE) -C tools/rcdump/ clean
	@#-$(MAKE) -C tools/rcmerge/ clean

install:
	-mkdir        $(INSTALL_INCLUDE_DIR)
	cp $(HEADERS) $(INSTALL_INCLUDE_DIR)
	cp bin/*.so   $(INSTALL_LIBS_DIR)
	cp bin/*.a    $(INSTALL_LIBS_DIR)
	ldconfig
	@#$(MAKE) -C tools/rcadd/ install
	$(MAKE) -C tools/rcdump/ install
	@#$(MAKE) -C tools/rcmerge/ install
